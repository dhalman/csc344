#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

typedef struct wavheader {
   char     id[4];          // should always contain "RIFF"
   uint32_t totallength;    // total file length minus 8
   char     wavefmt[8];     // should be "WAVEfmt "
   uint32_t format;         // 16 for PCM format
   uint16_t pcm;            // 1 for PCM format
   uint16_t channels;       // channels
   uint32_t frequency;      // sampling frequency
   uint32_t bytes_per_second;
   uint16_t bytes_by_capture;
   uint16_t bits_per_sample;
   char     data[4];        // should always contain "data"
   uint32_t bytes_in_data;
} header;

void printHeader(header *h) {
   int i;

   printf("\nHeader:\nRIFF: ");

   for (i = 0; i < sizeof(h->id); ++i) {
      printf("%c", h->id[i]);
   }

   printf("\nlength: %d\n", h->totallength);
   printf("fmt: %s\n", h->wavefmt);
   printf("format: %d\n", h->format);
   printf("pcm: %d\n", h->pcm);
   printf("channels: %d\n", h->channels);
   printf("frequency: %d\n", h->frequency);
   printf("bytes per second: %d\n", h->bytes_per_second);
   printf("capture: %d\n", h->bytes_by_capture);
   printf("bits per sample: %d\ndata: ", h->bits_per_sample);

   for (i = 0; i < sizeof(h->data); ++i) {
      printf("%c", h->id[i]);
   }

   printf("\ndata bytes: %d\n", h->bytes_in_data);
}

void printHex(uint8_t *buffer, int size, int perLine) {
   int i;

   printf("\n\nHex Dump:\n");

   for (i = 0; i < size; ++i) {
      if (i % perLine) {
         printf(" ");
      } else {
         printf("\n");
      }
      printf("%X", buffer[i]);
   }

   printf("\n\nHex END:\n");
}

void printBuffer(int16_t *samples, int size) {
   int i;

   printf("\nData:\n");

   for (i = 0; i < size; ++i) {
      printf("%d\n", samples[i]);
   }

   printf("\n-END-\n");
}

void reverseBuffer(uint8_t *samples, uint32_t size, int channels, uint16_t bitDepth) {
   uint8_t tmp;
   int i, j, k;
   uint8_t bytes_per_sample = bitDepth / 8;

   //printHex((uint8_t *)samples, size, bytes_per_sample);

   for (i = 0; i <= size / 2; i += bytes_per_sample) {
      // Swap #bytes per sample
      for (k = bytes_per_sample; k > 0; --k) {
         // Swap byte
         tmp = samples[i + bytes_per_sample - k];
         samples[i + bytes_per_sample - k] = samples[size - i - k];
         samples[size - i - k] = tmp;
      }
   }

   //printHex((uint8_t *)samples, size, bytes_per_sample);

   /*
   for (i = 0; i < size / 2; i += channels) {
      for (j = channels; j > 0; --j) {
         tmp = samples[i + channels - j];
         samples[i + channels - j] = samples[size - i - j];
         samples[size - i - j] = tmp;
      }
   }
   */
}

int checkArgs(int argc, char**argv) {
   // Ensure input file is given
   if (argc != 2) {
      printf("Wrong arg count\n");
      return 1;
   }

   // Ensure input file is wav
   if (!strstr(argv[1], ".wav")) {
      printf("Not a .wav file\n");
      return 1;
   }

   return 0;
}

int main(int argc, char **argv) {
   FILE *infile, *outfile; 
   int bytesRead, i; 
   unsigned long fPos;
   double bitRate, random;
   double duration;
   char *buffer;
   header wavHeader;
   int ret = 0;
   int payloadSize = 0;

   // Check arguments
   if (checkArgs(argc, argv)) {
      printf("Could not complete operation. Bad arguments\n");
      return 1;
   }
   
   // Check input file open
   if (!(infile = fopen(argv[1], "r"))) {
      printf("Could not open %s for reading.\n", argv[1]);
      return 1; 
   }

   // Check output file open
   if (!(outfile = fopen("output.wav", "w+"))) {
      printf("Could not open output.wav for writing.\n");
      fclose(infile);
      return 1;
   }

   // Read header
   fseek(infile, 0, SEEK_SET);
   fread(&wavHeader, 1, sizeof(header), infile);
   //printHeader(&wavHeader);

   // Read data
   buffer = malloc(wavHeader.totallength - sizeof(header));
   payloadSize = fread(buffer, 1, wavHeader.totallength - sizeof(header), infile);

   if (payloadSize != wavHeader.totallength - sizeof(header)) {
      printf("payload does not match header\n");
   }

  // printBuffer((int16_t *)buffer, wavHeader.bytes_in_data);
   printHex((uint8_t *)&wavHeader, sizeof(header), 1);

   // Write header
   fwrite(&wavHeader, 1, sizeof(header), outfile);

   // Perform modification
   reverseBuffer((uint8_t *)buffer, 
                  wavHeader.bytes_in_data,
                  wavHeader.channels,
                  wavHeader.bits_per_sample);

  // printBuffer((int16_t *)buffer, wavHeader.bytes_in_data);

   // Mirror sound: concatenate reverse sound to original
   fwrite(buffer, 1, payloadSize, outfile);

   // Clean house
   fclose(infile);
   fclose(outfile);
   free(buffer);

   return ret;
}
