#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void cark();
void ozdegerbul();
void schur();
void nilpotent();

void cark()
{

    int i,c,random;
    int x;// carkin kac defa dönecegi
    printf("cark kac kere donsun: ");
    scanf("%d",&x);

    for(i=1; i<=x; i++)
    {
        random=(rand()%(240-1))+1;
        printf("[%d]. sayi = %d\n",i,random);//carkin kac defa donecekse atayacagi sayilar
    }
    c=(random%4)+1;
    //ozdeger bulma,schur teoremi,ozvektor bulma,nilpotent matris hesaplarýndan ozvektor bulunamamaktadýr.
    //c degeri 3 gelirse program biter.
    printf("%d\n",c);

    if(c==1)//ozdeger islemi sarti
    {
        ozdegerbul();
    }
    else if(c==2)//Schur matris sarti
    {
        schur();
    }
    else if(c==4)//Nilpotent matris sarti
    {
        nilpotent();
    }

}
void ozdegerbul()
{
    printf("----------ozdeger hesabi----------\n\n");//1x1 2x2 3x3 icin sorunsuz calýsmaktadir.
    FILE *file1;
    file1=fopen("ozdegerbul.txt","w");//dosyanin adi belirlendi
    int n,i,j,k;
    double t,t2,t1,toplam=0;
    double det,delta;
    double lambda1, lambda2, lambda3;

    printf("nxn matris icin n?=");
    scanf("%d",&n);//matrisin eleman sayisi istendi . alindi
    int matris[n][n],matris2[n][n],matriscarp[n][n];

    printf("matrisin elamanlari:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d",&matris[i][j]);//matris deger alim islemi
            matris2[i][j]=matris[i][j];//matris carpma islemi kolayligi saglar.
        }
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fprintf(file1,"%5d",matris[i][j]);// matris yazdirma islemi
        }
        fprintf(file1,"\n");
    }
    if(n==1)
    {
        for(i=0; i<n; i++)
        {
            fprintf(file1,"matrisin ozdegeri=%d",matris[i][i]);//1x1 matris ozdegeri
        }

    }

    else if(n==2)
    {
        /*karakteristik polinom kurallari kullanilmistir.*/
        fputs("ax^2+bx+c denklemi üzerinden islem yapildi.\n",file1);
        fputs("islemler karakteristik polinomlar uzerinden yapilmistir.\n",file1);
        for(i=0; i<n; i++)
        {
            toplam+=matris[i][i];//2x2 matris kosegen toplami
        }

        t=toplam;
        double ee=1;
        fprintf(file1,"a =%.2lf\n",ee);//en buyuk dereceeli polinomun katsayisi
        fprintf(file1,"b (matris kosegen toplami)=%.2lf\n",t);//2x2 matris kosegen toplami yazdirma islemi


        det = matris[0][0]*matris[1][1] - matris[1][0]*matris[0][1];//determinant hesabi

        fprintf(file1,"\nc  (Determinant  2x2 matrix): %.2lf\n",det);//determinant yazdirma islemi
        t=t*-1;
        delta=(t*t)-(4*1*det);//matematiksel islem icin delta hesabi
        fprintf(file1,"b^2-(4ac)delta=%.2lf\n\n",delta);

        if(delta<0)
            fprintf(file1,"reel kok yoktur.");//sanal deger yazdirma islemi yapýlmadi.
        else
        {
            lambda1=(-t+sqrt(delta))/2;//ozdeger1 hesabi
            lambda2=((-t)-sqrt(delta))/2;//ozdeger2 hesabi
            fprintf(file1,"lambda1= %lf lambda2= %lf\n",lambda1,lambda2);//ozdegerler hesaplandi yazildi.

        }

    }
    else if(n==3)
    {
        /* cubic fonksiyonlari kullanilmistir.*/
        double b,c,ax,q,g,z,w,s,x,e,u,r,f,v,o,y,h;

        det= matris[0][0]*((matris[1][1]*matris[2][2]) - (matris[2][1]*matris[1][2]))-matris[0][1]*(matris[1][0]*matris[2][2]- matris[2][0]*matris[1][2]) + matris[0][2]*(matris[1][0]*matris[2][1] - matris[2][0]*matris[1][1]);
        //3x3 determinant hesabi
        fprintf(file1,"ax^3+bx^2+cx+d denklemi uzerinden islem yapilacaktir.\n\n\n\n");
        fputs("islemler karakteristik polinomlar uzerinden yapilmistir.\n",file1);

        fprintf(file1,"\ndeterminant 3X3 matrix . dnin degeri= %.2lf\n",det);
        ax=-1;//en buyuk dereceli bilinmeyenin katsayisi
        fprintf(file1,"a nin degeri=%lf\n",ax);//ax^3 icin a her zaman a=-1
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                for(k=0; k<n; k++)
                {
                    toplam+=matris[i][k]*matris2[k][j];//matris carpma islemi
                }
                matriscarp[i][j]=toplam;
                toplam=0;

            }
        }
        toplam=0;
        for(i=0; i<n; i++)
        {
            toplam+=matris[i][i];
        }
        b=toplam;
        fprintf(file1,"b nin degeri=%.2lf\n",b);//3x3 matrisin kosegen toplami

        toplam=0;
        for(i=0; i<n; i++)
        {
            toplam+=matriscarp[i][i];//matrisin karesinin kosegen toplama islemi
        }
        t1=toplam;
        fprintf(file1,"karesinin kosegen toplami=%.2lf\n",t1);//matrisin karesinin kosegen toplami

        t2=(b*b);
        fprintf(file1,"kosegenin toplam karesi=%.2lf\n",t2);//matrisin kosegenlerinin toplaminin karesi

        c=((t1-t2)/2);
        fprintf(file1,"c nin degeri=%.2lf\n",c);//cx deki c degeri hesaplanip yazildi.


        /*cubic formul yardim alinarak yapildi.*/
        q = ((3*c/ax)-((b*b)/(ax*ax)))/3;//trigonomik ve hiperbolik cozum formulleri
        g = ((2*(b*b*b)/(ax*ax*ax))-(9*b*c/(ax*ax))+(27*det/ax))/27;//trigonomik ve hiperbolik cozum formulleri
        z= ((g*g)/4)+((q*q*q)/27);

        fprintf(file1,"q=%lf g=%lf z=%lf\n\n\n",q,g,z);
        //uc gercek kok icin trigonometrik cozum uygulandi.
        if(q==0 && g==0 && z==0)
        {
            lambda1 = pow((det/ax),(double)1/3);
            lambda2 = pow((det/ax),(double)1/3);
            lambda3 = pow((det/ax),(double)1/3);

            fprintf(file1,"lambda1:%lf lambda2:%lf lambda3:%lf\n",lambda1,lambda2,lambda3);
        }
        //uc gercek kok icin trigonometrik cozum uygulandi.
        else if(z<=0)
        {
            w = pow((((g*g)/4)-z),(double)1/2);
            s = pow(w,(double)1/3);
            x = acos((g/(2*w))*-1);
            e = s * -1;
            u = cos(x/3);
            r = sqrt(3) * sin(x/3);
            f = (b/(3*ax))*-1;
            lambda1 = (2*s)*u-(b/(3*ax));
            lambda2 = e * (u+r) + f;
            lambda3 = e * (u-r) + f;

            fprintf(file1,"lambda1:%lf lambda2:%lf lambda3:%lf\n",lambda1,lambda2,lambda3);
        }
        /*reel olmayan koklere ulasildi.trigonometrik cozumlerden olumlu sonuc alinamadi.
        tek koku kurtarmak icin hiperbol cozumune basvuruldu.*/
        else if(z>0)
        {
            v = ((g/2)*-1)+pow(z,0.5);
            o = pow(v,(double)1/3);
            y = ((g/2)*-1)-pow(z,0.5);
            h = pow((y),(double)1/3);
            lambda1 = (o+h) - (b/(3*ax));


            fprintf(file1,"lambda1:%lf (2 tane daha kok vardir ama reel olmadigi icin islem yapilmadi.\n",lambda1);
        }



    }

    printf("islemler ozdegerbul.txt dosyasina yazildi.\n");
    fclose(file1);
}
void schur()
{
    FILE *file2;
    file2=fopen("schur.txt","w");//schur teoremi islemleri yazilacagi dosya acildi

    fprintf(file2,"--------------schur teoremi--------------\n\n");//1x1 2x2 3x3 icin sorunsuz calismaktadir.
    fprintf(file2,"----------once ozdeger hesabi yapilacak----------\n\n");

    int n,i,j,k;
    double t,t2,t1,toplam=0;
    double aa=0,bb=0,det,delta,lambda1,lambda2,lambda3;


    printf("-----------------schur teoremi--------------\n\n");

    printf("nxn matris icin n?=");
    scanf("%d",&n);//matrisin eleman sayisi alindi

    int matris[n][n],matris2[n][n],matriscarp[n][n];
    double lambda[n];

    printf("matrisin elamanlari:\n");

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d",&matris[i][j]);//matris deger alim islemi
            matris2[i][j]=matris[i][j];//matris carpma islemi kolayligi saglar.
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fprintf(file2,"%5d",matris[i][j]);// matris yazdirma islemþ
        }
        fprintf(file2,"\n");
    }
    if(n==1)
    {
        for(i=0; i<n; i++)
        {
            fprintf(file2,"lambda=%d\n\n",matris[i][i]);//1x1 matris ozdegeri
            fprintf(file2,"lamda ve matris elemanlarinin kareleri toplami ayni olacagi icin schur teoremine uygun degildir.");
        }

    }

    else if(n==2)
    {
        /*karakteristik polinom kurallari kullanilmistir.*/
        fputs("ax^2+bx+c denklemi üzerinden islem yapildi.\nkarakteristik polinomlar ile cozum uzretildi",file2);

        for(i=0; i<n; i++)
        {
            toplam+=matris[i][i];//2x2 matris kosegen toplami
        }

        t=toplam;
        double ee=1;
        fprintf(file2,"a =%.2lf\n",ee);
        fprintf(file2,"b  (matris kosegen toplami)=%.2lf\n",t);//2x2 matris kosegen toplami yazdirma islemi


        det = matris[0][0]*matris[1][1] - matris[1][0]*matris[0][1];//determinant hesabi

        fprintf(file2,"\nc  (Determinant  2x2 matrix:)%.2lf\n",det);//determinant yazdirma islemi
        t=t*-1;
        delta=(t*t)-(4*1*det);//matematiksel islem icin delta heabi
        fprintf(file2,"b^2-(4ac) delta=%.2lf\n",delta);

        if(delta<0)
        {
            fprintf(file2,"reel kok yoktur.\n");//sanal deger yazdirma islemi yapýlmadi.
            fprintf(file2,"ozdeger hesabi yapilamadigi icin schur teoremi hakkinda yorum yapilamadi.");
        }
        else
        {
            lambda1=((-t)+sqrt(delta))/2;
            lambda2=((-t)-sqrt(delta))/2;
            lambda[0]=lambda1;
            lambda[1]=lambda2;
            fprintf(file2,"lambda1= %lf lambda2= %lf\n\n\n",lambda1,lambda2);//ozdegerler hesaplandi yazildi.
            for(i=0; i<n; i++)
            {
                aa+=pow(lambda[i],2);
            }

            for(i=0; i<n; i++)
            {
                for(j=0; j<n; j++)
                {
                    bb+=pow(matris[i][j],2);
                }

            }
            fprintf(file2,"%lf\n",aa);//ozdeger elemanlarinin karesi alinip toplandi ve yazildi.
            fprintf(file2,"%lf\n",bb);//matrisin elemanlarinin karelerinin toplami

            if(aa>bb)
            {
                fprintf(file2,"%lf>%lf \nozdegerlerin karesi matrisin elemanlarinin karelerinin toplamindan büyüktür.",aa,bb);
            }
            else if(aa<=bb)
            {
                fprintf(file2,"%lf=>%lf \nozdegerlerin karesi matrisin elemanlarinin karelerinin toplamindan büyük degildir.",bb,aa);
            }

        }


    }

    else if(n==3)
    {
        /*cardono methodu kullanilmistir.*/
        double b,c,ax,q,g,z,w,s,x,e,u,r,f,v,o,y,h;
        det= matris[0][0]*((matris[1][1]*matris[2][2]) - (matris[2][1]*matris[1][2]))-matris[0][1]*(matris[1][0]*matris[2][2]- matris[2][0]*matris[1][2]) + matris[0][2]*(matris[1][0]*matris[2][1] - matris[2][0]*matris[1][1]);
        //3x3 determinant hesabi
        fprintf(file2,"ax^3+bx^2+cx+d denklemi uzerinden islem yapilacaktir.\n\n\n\n");
        fprintf(file2,"\ndeterminant 3X3 matrix . dnin degeri= %.2lf\n",det);
        ax=-1;
        fprintf(file2,"a nin degeri=%lf\n",ax);//ax^3 icin a her zaman a=-1
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                for(k=0; k<n; k++)
                {
                    toplam+=matris[i][k]*matris2[k][j];//matris carpma islemi
                }
                matriscarp[i][j]=toplam;
                toplam=0;
                //printf("%d ",matriscarp[i][j]);
            }
            //printf("\n");
        }
        toplam=0;
        for(i=0; i<n; i++)
        {
            toplam+=matris[i][i];
        }

        b=toplam;
        fprintf(file2,"b nin degeri=%.2lf\n",b);//3x3 matrisin kosegen toplami

        toplam=0;
        for(i=0; i<n; i++)
        {
            toplam+=matriscarp[i][i];//matrisin karesinin kosegen toplami
        }
        t1=toplam;
        fprintf(file2,"karesinin kosegen toplami=%.2lf\n",t1);

        t2=(b*b);
        fprintf(file2,"kosegenin toplam karesi=%.2lf\n",t2);//matrisin kosegenlerinin toplaminin karesi

        c=((t1-t2)/2);
        fprintf(file2,"c nin degeri=%.2lf\n",c);//cx deki c degeri hesaplanip yazildi.


        /*cubic formul yardim alinarak yapildi.*/
        q = ((3*c/ax)-((b*b)/(ax*ax)))/3;
        g = ((2*(b*b*b)/(ax*ax*ax))-(9*b*c/(ax*ax))+(27*det/ax))/27;
        z= ((g*g)/4)+((q*q*q)/27);
        fprintf(file2,"q=%lf g=%lf z=%lf\n\n\n",q,g,z);
        //trigonometrik kok cozumleri kullanildi.
        if(q==0 && g==0 && z==0)   // 3 adet kok belirtir bu kosullar
        {
            lambda1 = pow((det/ax),(double)1/3);
            lambda2 = pow((det/ax),(double)1/3);
            lambda3 = pow((det/ax),(double)1/3);

            fprintf(file2,"lambda1:%lf lambda2:%lf lambda3:%lf\n\n",lambda1,lambda2,lambda3);
            aa=pow(lambda1,2)+pow(lambda2,2)+pow(lambda3,2);
            for(i=0; i<n; i++)
            {
                for(j=0; j<n; j++)
                {
                    bb+=pow(matris[i][j],2);
                }
            }
            fprintf(file2,"%lf\n",aa);//ozdeger elemanlarinin karesi alinip toplandi ve yazildi.
            fprintf(file2,"%lf\n",bb);//matrisin elemanlarinin karelerinin toplami
            if(aa>bb)
            {
                fprintf(file2,"%lf>%lf \nozdegerlerin karesi matrisin elemanlarinin karelerinin toplamindan büyüktür.",aa,bb);
            }
            else if(aa<=bb)
            {
                fprintf(file2,"%lf=>%lf \nozdegerlerin karesi matrisin elemanlarinin karelerinin toplamindan büyük degildir.",bb,aa);
            }
        }
        else if(z<=0)//3 adet kok belirtir bu kosullar
        {
            w = pow((((g*g)/4)-z),0.5);
            s = pow(w,(double)1/3);
            x = acos((g/(2*w))*-1);
            e = s * -1;
            u = cos(x/3);
            r = sqrt(3) * sin(x/3);
            f = (b/(3*ax))*-1;
            //sinüs ve cosinüs imajinal hesap yapilamadigi icin formul uzerinden direkt cevrilerek yazildi.
            lambda1 = (2*s)*u-(b/(3*ax));
            lambda2 = e * (u+r) + f;
            lambda3 = e * (u-r) + f;

            fprintf(file2,"lambda1:%lf lambda2:%lf lambda3:%lf\n\n",lambda1,lambda2,lambda3);
            aa=pow(lambda1,2)+pow(lambda2,2)+pow(lambda3,2);
            for(i=0; i<n; i++)
            {
                for(j=0; j<n; j++)
                {
                    bb+=pow(matris[i][j],2);
                }
            }
            fprintf(file2,"%lf\n",aa);//ozdeger elemanlarinin karesi alinip toplandi ve yazildi.
            fprintf(file2,"%lf\n",bb);//matrisin elemanlarinin karelerinin toplami
            if(aa>bb)
            {
                fprintf(file2,"%lf>%lf \nozdegerlerin karesi matrisin elemanlarinin karelerinin toplamindan büyüktür.",aa,bb);
            }
            else if(aa<=bb)
            {
                fprintf(file2,"%lf=>%lf \nozdegerlerin karesi matrisin elemanlarinin karelerinin toplamindan büyük degildir.",bb,aa);
            }
        }

        else if(z>0)
        {
            /*hiperbol kok cozumu uygulandi.*/
            v = ((g/2)*-1)+pow(z,0.5);
            o = pow(v,(double)1/3);
            y = ((g/2)*-1)-pow(z,0.5);
            h = pow((y),(double)1/3);
            lambda1 = (o+h) - (b/(3*ax));

            fprintf(file2,"lambda1:%lf \n2 adet daha kok bulunmaktadir.ancak kokler reel olmadigi icin ozdeger hesabi yapilamadi.\n",lambda1);
            fprintf(file2,"dolayisiyla schur teoremi hakkinda yorum yapilamadi.\n");
        }
    }

    printf("islemler schur.txt dosyasina yazildi.\n");
    fclose(file2);

}


void nilpotent()
{
    printf("--------------Nilpotent Matris --------------\n");
    FILE *file4;
    file4 = fopen("nilpotent.txt ","w");//nilpotent islemleri yazilacagi dosya belirlendi.

    int n,i,j,k,l,m;
    printf("nxn matris icin n:");
    scanf("%d",&n);
    int matris[n][n],matris1[n][n];
    fputs("random atanan matris  \n",file4);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            matris[i][j]=-15+rand()%31;//(-15,15) araligi olamsi icin -15 in uzerine 30 sayisini ekledim.
            matris1[i][j]=matris[i][j];
            fprintf(file4,"%5d ",matris[i][j]);
        }
        fprintf(file4,"\n");
    }


    int matriscarp[n][n];

    int toplam=0,sayac;

    fputs("carpma islemi sonucu \n",file4);
    for(sayac=0; sayac<n; sayac++)
    {
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                for(k=0; k<n; k++)
                {
                    toplam+=matris[i][k]*matris1[k][j];//matris carpma islemi yapildi
                }
                matriscarp[i][j]=toplam;
                toplam=0;
            }
        }
        for(l=0; l<n; l++)
        {
            for(m=0; m<n; m++)
            {
                matris1[l][m]=matriscarp[l][m];
                fprintf(file4,"%4d ",matriscarp[l][m]);//carpma islemi sonuclari yazildi.
            }
            fprintf(file4,"\n");
        }
        fprintf(file4,"\n");
    }

    printf("\n");

    int a=0;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(matriscarp[i][j]==0)//matris degerleri 0'a esit mi.
            {
                a++;
            }
        }
    }
    if(n*n==a)
    {
        printf("nilpotent matris.\n\n");
    }
    else
    {
        printf("nilpotent matris degil.\n\n");
    }

    printf("islemler nilpotent.txt dosyasina yazildi.\n");
    fclose(file4);
}

int main()
{
    srand(time(NULL));
    cark();

    return 0;
}


