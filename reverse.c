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

void printBuffer(int16_t *samples, int size) {
   int i;

   printf("\nData:\n");

   for (i = 0; i < size; ++i) {
      printf("%d\n", samples[i]);
   }

   printf("\n-END-\n");
}

void reverseBuffer(int16_t *samples, int size) {
   int16_t tempLeft, tempRight;
   int i;

   // 2 channel handles left and right samples serially.
   for (i = 0; i < size / 2; i += 2) {
      tempLeft = samples[i];
      tempRight = samples[i + 1];

      samples[i] = samples[size - i - 2]; 
      samples[i + 1] = samples[size - i - 1]; 

      samples[size - i - 2] = tempLeft;
      samples[size - i - 1] = tempRight;
   }
}

int checkArgs(int argc, char**argv) {
   if (argc != 2) {
      printf("Wrong arg count\n");
      return 1;
   }

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

   if (checkArgs(argc, argv)) {
      printf("Could not complete operation. Bad arguments\n");
      return 1;
   }
   
   if ((infile = fopen(argv[1], "r"))) {
      if ((outfile = fopen("output.wav", "w+"))) {
         fseek(infile, 0, SEEK_SET);
         fread(&wavHeader, 1, sizeof(header), infile);
         //printHeader(&wavHeader);

         buffer = malloc(wavHeader.bytes_in_data);
         fread(buffer, 1, wavHeader.bytes_in_data, infile);

         //printBuffer((int16_t *)buffer, wavHeader.bytes_in_data / 2);
         reverseBuffer((int16_t *)buffer, wavHeader.bytes_in_data / 2);
         //printBuffer((int16_t *)buffer, wavHeader.bytes_in_data / 2);

         fwrite(&wavHeader, 1, sizeof(header), outfile);
         fwrite(buffer, 1, wavHeader.bytes_in_data, outfile);

         fclose(infile);
         fclose(outfile);
         free(buffer);
      } else {
         printf("Could not open output.wav for writing.\n");
         fclose(infile);
         return 1;
      }
   } else {
      printf("Could not open %s for reading.\n", argv[1]);
      return 1; 
   }

   return 0;
}
