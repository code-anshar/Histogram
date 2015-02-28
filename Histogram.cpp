# Histogram
//Source code from stackoverflow.com
//Edit and modified by : anshar iriansyah, for "Pengolahan Citra" in Engineering Faculty of Sultan Hasanuddin

#include <cstdio> 
#include <cstdlib>
#include <iostream>
#include <cstring>
#include"pgmlib.h"
using namespace std;

void print_histogram_table(int *histog);

main() 
{
  FILE *fp;
  
  int i,j, height, width;
  char line[100];
  char namein[100];
  unsigned char image[NN];
  
  unsigned char pixel_value; //255

  cout<<"Nama file yang Dibaca *pgm = ";
  cin>>namein;
  
  fp = fopen(namein,"r");	
  
  read_pgm(namein, &width, &height, image);
  //cout<<height<<" "<<width<<"\n"; //Buat cek ukuran
  
  // membaca imputan 4x, yang dipake cuman yang ke-4
  fgets (line,100,fp); 
  fgets (line,100,fp);
  fgets (line,100,fp);
  fgets (line,100,fp);

  // set semua rentang nilai = 0
  int histo[height*width];
  for (int x=0; x<=(height*width); x++)
  {    
        histo[x] = 0;
  }

  for(j=0;j<height;j++) 
  {
     for(i=0;i<width;i++) 
	 {
        fread(&pixel_value, sizeof(unsigned char), 1, fp);
         	// Buat cek secara spesifik nilai tiap bas_kom :
			//printf("row num. %d column num. %d    pixel value=%d\n",j,i,pixel_value);  
       	histo[pixel_value]++;
     }
  }

  print_histogram_table(histo); // buat histogram
  fclose(fp); //close file tadi
}

void print_histogram_table(int *histog)
{
  char nameout[100];
  FILE *fo;
  
  cout<<"Nama file tempat Penyimpanan *dat = ";
  cin>>nameout;
  
  fo = fopen(nameout,"w");
  
  for (int x=0; x <= 255; x++) 
  {
     if ( histog[x] != 0)
		cout<<"Nilai "<<x<<" sebanyak "<<histog[x]<<"\n";
		fprintf(fo, "%d, %d\n", x, histog[x]); 
  }
  
  fclose(fo);
}
