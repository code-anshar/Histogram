//extension for PGM file

#include <stdio.h>
#include <stdlib.h>
#define NN  1600000 /* im*jm*col<NN */

int check_pgm(char *headbuf,FILE *fp,int *width,int *height)
{
        char buf[100];
        int i=0;
        int tw,th;
        fgets(buf,sizeof(buf),fp);
        if(buf[0]=='P' && buf[1]=='5')
        {
                if(headbuf) headbuf=buf;
				do {
                        fgets(buf,sizeof(buf),fp);
                        if(headbuf) headbuf=buf;
                } while(buf[0]=='#');
				
                sscanf(buf,"%d%d",&tw,&th);
                /*      NULL check      */
                if(width) *width=tw;
                if(height) *height=th;
                do {
                        fgets(buf,sizeof(buf),fp);
                        if(headbuf) headbuf=buf; //strcat(headbuf,buf);
                } while(buf[0]=='#');
                return ftell(fp);
        }
        else
        {
                fputs("Not a PGM file....\n",stderr);
                fclose(fp);
                return 0;
        }
}

void read_pgm(char filename[],int *im,int *jm,unsigned char image[])
{
        int i,j;
        FILE *fp;
        char buf[10000];

        if((fp=fopen(filename,"rb"))==NULL)
        {
                printf("file %s can not open ",filename);
                exit;
        }

        check_pgm(buf,fp,im,jm);
        fread(image,sizeof(unsigned char),(*im)*(*jm),fp);
        fclose(fp);
}


void write_pgm(char filename[],int im,int jm,unsigned char image[])
{
        int i,j;
        int bits=255;
        FILE *fp;

        if((fp=fopen(filename,"wb"))==NULL)
        {
                perror("file can not open ");
                exit;
        }

        fprintf(fp,"%s\n","P5");
        fprintf(fp,"%s\n","#");
        fprintf(fp,"%d %d\n",im,jm);
        fprintf(fp,"%d\n",bits);

        fwrite(image,sizeof(unsigned char),im*jm,fp);
        fclose(fp);
}
