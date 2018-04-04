/*
Truong dai hoc Bach Khoa Ha Noi
Nguyen Dinh Quan
MSSV: 20166622
Hoc ki: 20172
Chuong trinh quan ly sinh vien
	+ Su dung tep lam co so du lieu
	+ Du lieu se duoc doc/ghi o file ds.txt duoi dang tep nhi phan va duoc luu lai duoi dang file van ban danhsach.txt
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
struct SV{
    char ht[50];
    int tuoi;
    char mssv[20];
    float diemKTLT;
};

typedef struct SV student;
int n;
int  size   =   sizeof(student);
void bosung();
void sapxep();
void inds();
void suachua();
void chen();
int sosanhten(char ten1[50], char ten2[50]);
void hoanvi();
void capnhatN();
void xuatFile();
void format(char sth[50]);
int main()
{
    capnhatN();
    char ch;
	while(1){
		system("cls");
		printf("Du lieu duoc doc ghi tu file nhi phan ds.txt va duoc luu thanh file van ban danhsach.txt");
		printf("\n CHUONG TRINH QUAN LY SINH VIEN ");
		printf("\n 	1. Bo sung danh sach");
		printf("\n 	2. Sua chua");
		printf("\n 	3. In danh sach");
		printf("\n 	4. Xuat FILE");
		printf("\n 	5. Sap xep danh sach");
		printf("\n 	Bam 1-4 de chon, phim bat ki de ket thuc\n");
		fflush(stdin);
		ch = getch();
		if(ch == '1') bosung();
		else if(ch == '2') suachua();
		else if(ch == '3') inds();
		else if(ch == '4') xuatFile();
		else if(ch == '5') sapxep();
		else
		{
			fflush(stdin);
			printf("\n chan roi a ? Y/N");
			ch = getch();
			if(ch == 'Y' || ch == 'y') break;
		}
	}
	//xuatFile();
	return 0;
}
void capnhatN(){
    FILE *fs;
    int i;
    fs = fopen("ds.txt","r+");
    fseek(fs,0,2);
    n = ftell(fs)/size;
    fclose(fs);
}
void bosung(){
    student st;
    FILE *fs;
    fs = fopen("ds.txt","ab");
    // xac dinh so ban ghi
    fseek(fs, 0, 2);
    n = ftell(fs)/size;
    while(1){
        printf("nguoi thu %d :\n", n+1);
        printf("Ho va ten: ");
        fflush(stdin);
        gets(st.ht);
        if(st.ht[0] == '\0') break;
        format(st.ht);
        printf("\nTuoi:");
        scanf("%d", &st.tuoi);
        printf("\nMSSV: ");
        fflush(stdin);
        gets(st.mssv);
        printf("\nDiem KTLT: ");
        scanf("%f", &st.diemKTLT);
        n++;
        fwrite(&st,size,1,fs);
    }
    fclose(fs);
}
void format(char sth[50]){
    sth[0] = toupper(sth[0]);
    for(int i = 1; i<strlen(sth);i++){
        if(sth[i-1] == ' ')
            sth[i] = toupper(sth[i]);
        else sth[i] = tolower(sth[i]);
    }
}
int sosanhten(char ten1[50], char ten2[50]){
	int l1 = strlen(ten1);
	int l2 = strlen(ten2);
	int i,j;
	for(i = l1-1; i > 0 ; i--)
		if(ten1[i] == ' ' )
		{
			i++;
			break;
		}
	for(j = l2-1; j > 0 ; j--)
		if(ten2[j] == ' ')
		{
			j++;
			break;
		}
//    ten1[i] = toupper(ten1[i]);
//    ten2[i] = toupper(ten2[j]);
	int flag = 0;
	while(i < l1 || j < l2)
	{
		if(ten1[i] == ten2[j])
		{
			i++;
			j++;
		}
		else if(ten1[i] > ten2[j])
		{
			flag = 1;
			i=l1;j=l2;
		}
		else
		{
			flag = -1;
			i=l1;j=l2;
		}
	}

	if(flag == 0)
	{
		if(strcmp(ten1,ten2) > 0 ) return 1;
		else return 0;
	}
	else if(flag == 1) return 1;
	else return 0;
}
void sapxep(){
    //GET DATA
    student st;
    int i=0;
    struct SV *mangSV;
    mangSV = (struct SV *) malloc(n * size);
    FILE *fs;
    fs = fopen("ds.txt","r+b");
    while( fread(&st,size,1,fs) > 0)
    {
        strcpy(mangSV[i].ht,st.ht);
        strcpy(mangSV[i].mssv,st.mssv);
        mangSV[i].tuoi     = st.tuoi;
        mangSV[i].diemKTLT = st.diemKTLT;
        i++;
    }
    //================
    //INSERTION SORT
    int j;
    student tmp;
    for(i = 1; i < n; i++)
    {
        j = i-1;
        strcpy(tmp.ht,mangSV[i].ht);
        strcpy(tmp.mssv,mangSV[i].mssv);
        tmp.tuoi = mangSV[i].tuoi;
        tmp.diemKTLT = mangSV[i].diemKTLT;
        while(j >= 0  && sosanhten(mangSV[j].ht,tmp.ht))
        {
        strcpy(mangSV[j+1].ht,mangSV[j].ht);
        strcpy(mangSV[j+1].mssv,mangSV[j].mssv);
        mangSV[j+1].tuoi     = mangSV[j].tuoi;
        mangSV[j+1].diemKTLT = mangSV[j].diemKTLT;
        j--;
        }
        strcpy(mangSV[j+1].ht,tmp.ht);
        strcpy(mangSV[j+1].mssv,tmp.mssv);
        mangSV[j+1].tuoi     = tmp.tuoi;
        mangSV[j+1].diemKTLT = tmp.diemKTLT;
    }
for(int t = 0; t < n;t++)
{
    printf("\n%s\n", mangSV[t].ht);
}
    rewind(fs);
    for(int i = 0; i < n;i++)
    {
        strcpy(st.ht,mangSV[i].ht);
        st.tuoi     = mangSV[i].tuoi;
        strcpy(st.mssv,mangSV[i].mssv);
        st.diemKTLT = mangSV[i].diemKTLT;
        fwrite(&st,size,1,fs);
    }
    free(mangSV);
    fclose(fs);
    getch();
}
void inds(){
    FILE *fs;
    student st;
    fs = fopen("ds.txt","rb");
    int i = 1;
    while(fread(&st,size,1,fs)  >  0){
        printf("\nnguoi thu %d:",i);
        printf("\nho ten: %s", st.ht);
        printf("\nTuoi: %d", st.tuoi);
        printf("\nMSSV: %s", st.mssv);
        printf("\nDiem KTLT: %f", st.diemKTLT);
        i++;
        }
    getch();
    fclose(fs);
}
void suachua(){
    student st;
    FILE *fs;
    int i;
    fs = fopen("ds.txt","r+b");
    while(1){
        printf("sua nguoi thu <nhap so 0 va nhan enter de huy viec chinh sua!>: ");
        int i;
        scanf("%d",&i);
        if(i  == '\0') break;
        fseek(fs,(i-1)*size,0);
        printf("\nnhap ho ten: ");
        fflush(stdin);
            gets(st.ht);
        if(st.ht[0] == '\0') break;
        format(st.ht);
        printf("\nnhap tuoi : ");
            scanf("%d",&st.tuoi);
        printf("\nnhap mssv : ");
        fflush(stdin);
            gets(st.mssv);
        printf("\nnhap diem KTLT : ");
            scanf("%f", &st.diemKTLT);
        fseek(fs, (i-1)*size, 0);
        fwrite(&st, size,1,fs);
    }
    fclose(fs);
}


void xuatFile(){
    FILE *fs, *ft;
    int i=0;
    student st;
    fs = fopen("ds.txt","r+b");
    ft = fopen("danhsach.txt","w+");
    fprintf(ft,"so ban ghi = %d\n",n);
    fprintf(ft,"%s   ||%s\t\t\t||\t%s\t||\t%s\t||\t%s\n","STT","Ho va ten","MSSV","Tuoi","Diem KTLT");
    fprintf(ft,"======||================================||==============||==============||===============\n");
    while(fread(&st,size,1,fs) > 0)
    {
        i++;
        fprintf(ft,"%d     ||",i);
        if(strlen(st.ht) <=15)
            fprintf(ft,"%s\t\t\t||\t",st.ht);
        else
            fprintf(ft,"%s\t\t||\t",st.ht);
        fprintf(ft,"%s\t||\t",st.mssv);
        fprintf(ft,"%d\t||\t",st.tuoi);
        fprintf(ft,"%2.3f\n",st.diemKTLT);

    }
    printf("DA GHI XONG FILE DANHSACH.TXT!");
    fclose(fs);
    fclose(ft);
    getch();
}

