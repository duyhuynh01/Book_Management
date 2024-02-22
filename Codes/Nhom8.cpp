#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
#include<conio.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
struct Sach
{
    char Ma_Sach[8], Ten_Sach[50], The_Loai[20],
    Nha_Xuat_Ban[30], Tac_Gia[20];
    int Tong_So_Luong, SL_HienTai, 
    So_Lan_Muon, Nam_XB, So_Trang;
};
typedef Sach DS_Sach[50];
struct ThoiGian
{
    int Ngay;
    int Thang;
    int Nam;
};
struct PhieuMuon
{
    char Ma_Phieu[10];
    ThoiGian Ngay_Muon;
    char Ho_Ten[30] ;
    int SL_Sach ;
};
typedef PhieuMuon DS_Phieu[350];
struct CTPM
{
    char Ma_Sach[8];
    char Ma_Phieu[10];
    char Tinh_Trang_Sach[50];
    bool Tra;
};
typedef CTPM DS_CTPM[350];
int  TimSach(DS_Sach a ,int n ,char c[8]);
int  TimMSPhieu(DS_Phieu b ,int m ,char c[10]);
void InChiTietPhieu(DS_Phieu b ,int m,char ms[10]);
void InChiTietSach(DS_Sach a,int n,char ms[8]);
DS_Sach a;
DS_Phieu b;
DS_CTPM c;
int n=0 ,m=0 ,k=0;//n la tong so sach , m la tong so phieu muon , k la tong so sach dc muon trong tung chi tiet phieu muon
//========================= HAM KIEM TRA NAM NHUAN (tra ve so ngay cua Nam ) ========================
int NamNhuan(int Nam)
{
    if((Nam%4==0 && Nam%100!=0)||(Nam%400==0)) return 366;
    else return 365;
}
//=================== HAM TRA VE SO NGAY CUA THANG ====================
int KiemTraThang(int Thang,int Nam)
{
    switch(Thang)
    {
    case 4:  return 30;
    case 6:  return 30;
    case 9:  return 30;
    case 11: return 30;
    case 2:
        if (NamNhuan(Nam)==366) return 28;
        else return 29;
    default: return 31;
    }
}
//================== HAM TINH SO NGAY KE TU NGAY DAU NAM =======================
int ViTri(int Ngay,int Thang,int Nam)
{
    int N=0,i;
    for(i=1;i<Thang;++i)
    {
       N=N+KiemTraThang(i,Nam);
    }
    return (N+Ngay);
}
//=============== HAM TINH SO NGAY GIUA 2 NAM =================
int KhoangCachNam(int namtruoc,int namsau)
{
      int N=0,i;
      i=namtruoc+1;
      for(i;i<namsau;++i)
      {
         N=N+NamNhuan(i);
      }
      return N;
}
//========================= HAM THEM DAU SACH MOI VAO THU VIEN  ========================
void ThemSach(DS_Sach a ,int &n)
{
    n++;
    cout<<"\n                         THEM MOT DAU SACH MOI VAO THU VIEN \n";
    cout<<"===============================================================================\n";
    nhap:  cout<<"Nhap Ma Sach: " ;
    cin>>a[n].Ma_Sach;
    if (TimSach(a ,n-1 ,a[n].Ma_Sach)!=0)
    {
        cout<<"Ma Sach Nay Da Co, Hay Nhap Lai \n";
        goto nhap;
    }
    cout<<"Nhap Ten Sach: ";
    cin.ignore();
    gets(a[n].Ten_Sach);
    cout<<"Nhap Ten The Loai: ";
    gets(a[n].The_Loai);
    cout<<"Nhap Ten Tac Gia: ";
    gets(a[n].Tac_Gia);
    cout<<"Nhap Ten Nha Xuat Ban: ";
    gets(a[n].Nha_Xuat_Ban);
    cout<<"Nhap Nam Xuat Ban: ";
    cin>>a[n].Nam_XB;
    cout<<"Nhap So Trang Cua Sach: ";
    cin>>a[n].So_Trang;
    cout<<"Nhap Tong So Luong Sach: ";
    cin>>a[n].Tong_So_Luong;
    a[n].SL_HienTai=a[n].Tong_So_Luong ;
    cout<<"\n---THEM SACH MOI THANH CONG--- ";
}
//===================HAM TIM MA SO SACH ========================
int TimSach(DS_Sach a ,int n ,char c[8])
{
    int i;
    i=1;
    while((i<=n)&& (strcmp(a[i].Ma_Sach,c)!=0))
        i++;   
    if (i>n) return 0;
    else return i;
}
//==========================HAM XOA THONG TIN SACH ==============================
void XoaSach(DS_Sach a ,int &n)
{
    char ms[8];
    int ViTri ;
    cout<<"\n                         XOA THONG TIN SACH  \n";
    cout<<"===============================================================================\n";
    cout<<"Nhap Vao Ma So Sach:" ;
    cin>>ms ;
    ViTri=TimSach(a,n,ms);
    if (ViTri==0)
        cout<<"KHONG CO MA SO SACH NAY \n";
    else
    {
        if(a[ViTri].SL_HienTai<a[ViTri].Tong_So_Luong)
            cout<<"\n SACH HIEN CO NGUOI MUON, KHONG THE XOA\n";
        else
        {  
            for(int i=ViTri;i<=n;i++)
                a[i]=a[i+1];
                n--;
                cout<<"---Xoa Thanh Cong---" ;
        }      
    }      
}
//===================== HAM SUA THONG TIN CUA MOT CUON SACH ========================
void SuaSach(DS_Sach a,int &n)
{
    char ms[8];
    int ViTri ,slmuon=0 ;
    cout<<"\n                         SUA THONG TIN SACH \n";
    cout<<"===============================================================================\n";
    cout<<"Nhap Vao Ma So Cua Sach:" ;
    cin>>ms ;
    ViTri=TimSach(a,n,ms);
    if (ViTri==0)
        cout<<"---KHONG CO MA SO SACH NAY---";
    else
    {
        InChiTietSach(a,n,ms);
        slmuon=a[ViTri].Tong_So_Luong-a[ViTri].SL_HienTai;
        cout<<"\nNHAP VAO THONG TIN MOI CHO QUYEN SACH \n";
        cout<<"Nhap Ten Sach: ";
        cin.ignore();
        gets(a[ViTri].Ten_Sach);
        cout<<"Nhap Ten The Loai: ";
        gets(a[ViTri].The_Loai);
        cout<<"Nhap Ten Tac Gia: ";
        gets(a[ViTri].Tac_Gia);
        cout<<"Nhap Ten Nha Xuat Ban: ";
        gets(a[ViTri].Nha_Xuat_Ban);
        cout<<"Nhap Nam Xuat Ban: ";
        cin>>a[ViTri].Nam_XB;
        cout<<"Nhap So Trang Cua Sach: ";
        cin>>a[ViTri].So_Trang;
        cout<<"Nhap Tong So Luong Sach: ";
        cin>>a[ViTri].Tong_So_Luong ;
        a[ViTri].SL_HienTai=a[ViTri].Tong_So_Luong-slmuon;
        cout<<"\n---SUA THONG TIN SACH THANH CONG---\n";
    }
}
//==================== HAM IN TOAN BO SACH CO TRONG THU VIEN ===================
void InToanBoSach(DS_Sach a,int n)
{
    cout<<"\n \n                                         DANH SACH CAC DAU SACH CO TRONG THU VIEN ";
    cout<<"\n  ===========================================================================================================================";
    cout<<"\n  |Ma Sach |           Ten Sach           |       Tac Gia      |  The Loai   | Nha Xuat Ban | Nam XB | So Trang | TSL |SL HC|";
    cout<<"\n  ==========================================================================================================================|";
    for(int i=1 ;i<=n;i++)
        cout<<"\n  |"<<a[i].Ma_Sach<<setw(8-strlen(a[i].Ma_Sach)+1)<<"|"<<a[i].Ten_Sach<<setw(30-strlen(a[i].Ten_Sach)+1)<<"|"<<a[i].Tac_Gia<<setw(20-strlen(a[i].Tac_Gia)+1)<<"|"<<a[i].The_Loai<<setw(13-strlen(a[i].The_Loai)+1)<<"|"
        <<a[i].Nha_Xuat_Ban<<setw(14-strlen(a[i].Nha_Xuat_Ban)+1)<<"|"<<setw(8)<<a[i].Nam_XB<<"|"<<setw(10)<<a[i].So_Trang<<"|"<<setw(5)<<a[i].Tong_So_Luong<<"|"<<setw(5)<<a[i].SL_HienTai<<"|";
    cout<<"\n  ===========================================================================================================================";        
}
//========================= HAM IN THONG TIN CHI TIET MOT CUON SACH ==========================
void InChiTietSach(DS_Sach a ,int n,char ms[8])
{
    int ViTri;
    ViTri=TimSach(a,n,ms);
    if(ViTri==0)
        cout<<"Khong Tim Thay Ma So Sach Nhap Vao \n";
    else
    {
        cout<<"\n    THONG TIN CHI TIET SACH \n"<<endl;
        cout<<"Ma Sach     : "<<a[ViTri].Ma_Sach<<endl;
        cout<<"Ten Sach    : "<<a[ViTri].Ten_Sach<<endl;
        cout<<"Tac Gia     : "<<a[ViTri].Tac_Gia<<endl;
        cout<<"The Loai    : "<<a[ViTri].The_Loai<<endl;
        cout<<"Nha Xuat Ban: "<<a[ViTri].Nha_Xuat_Ban<<endl;
        cout<<"Nam Xuat Ban: "<<a[ViTri].Nam_XB<<endl;
        cout<<"So Trang    : "<<a[ViTri].So_Trang<<endl;
        cout<<"Tong SL     : "<<a[ViTri].Tong_So_Luong<<endl;
        cout<<"SL Hien Con : "<<a[ViTri].SL_HienTai<<endl;
    }
}
//===================== HAM LIET KE CAC SACH THEO MOT THE LOAI =============================
void TimSachTheLoai(DS_Sach a ,int n)
{
    char tentheloai[20];
    int dem=0;
    cout<<"\n                         LIET KE CAC SACH THEO MOT THE LOAI \n";
    cout<<"===============================================================================\n";
    cout<<" Nhap Vao Ten The Loai Muon Tim: " ;
    cin.ignore();
    cin.getline(tentheloai,20);
    cout<<"\n  ============================================================================";
    cout<<"\n  |Ma Sach |                        Ten Sach                     | TSL |SL HC|";
    cout<<"\n  ============================================================================";
    for(int i=1;i<=n;i++)
    {
        if(strcmp(a[i].The_Loai,tentheloai)==0)
                { cout<<"\n  |"<<a[i].Ma_Sach<<setw(8-strlen(a[i].Ma_Sach)+1)<<"|"<<a[i].Ten_Sach<<setw(53-strlen(a[i].Ten_Sach)+1)<<"|"<<setw(5)<<a[i].Tong_So_Luong<<"|"<<setw(5)<<a[i].SL_HienTai<<"|"; dem++;}
    }
    cout<<"\n  ============================================================================";
    if(dem==0)
        cout<<"\n \n KHONG TIM THAY THE LOAI SACH MA BAN NHAP VAO \n";
}
//===================== HAM THONG KE CAC SACH DA CHO MUON HET TRONG THU VIEN ==================
void ThongKeSachHet(DS_Sach a,int n)
{
    cout<<"\n             CAC DAU SACH DA CHO MUON HET TRONG THU VIEN ";
    cout<<"\n  =======================================================================";
    cout<<"\n  |Ma Sach |                Ten Sach                |  The Loai   | TSL |";
    cout<<"\n  =======================================================================";
    for(int i=1;i<=n;i++)
        if(a[i].SL_HienTai==0)
            cout<<"\n  |"<<a[i].Ma_Sach<<setw(8-strlen(a[i].Ma_Sach)+1)<<"|"<<a[i].Ten_Sach
            <<setw(40-strlen(a[i].Ten_Sach)+1)<<"|"<<a[i].The_Loai<<setw(13-strlen(a[i].The_Loai)+1)
            <<"|"<<setw(5)<<a[i].Tong_So_Luong<<"|";
    cout<<"\n  =======================================================================";        
}
void ThongKeSachMuonNhieu()
{
    DS_Sach d;
    Sach tam ;
    int h;
    for(int i=1;i<=n;i++)
        d[i]=a[i];
    int post;
    for(int i=2;i<=n;i++)
    {
        tam=d[i];
        post=i-1;
        while(post>=1 && d[post].So_Lan_Muon>tam.So_Lan_Muon)
            {d[post+1]=d[post];post--;}
        d[post+1]=tam; 
    }
    cout<<"\n           TOP 5 DAU SACH CHO MUON NHIEU NHAT TRONG THU VIEN ";
    cout<<"\n  =======================================================================";
    cout<<"\n  |Ma Sach |                Ten Sach                |  The Loai   | SLM |";
    cout<<"\n  =======================================================================";
    if(n>5) h=n-5;  
    else  h=0;
    for(int i=n;i>h;i--)
        if(d[i].So_Lan_Muon!=0)
        {
        cout<<"\n  |"<<d[i].Ma_Sach<<setw(8-strlen(d[i].Ma_Sach)+1)<<"|"<<d[i].Ten_Sach
        <<setw(40-strlen(d[i].Ten_Sach)+1)<<"|"<<d[i].The_Loai<<setw(13-strlen(d[i].The_Loai)+1)
        <<"|"<<setw(5)<<d[i].So_Lan_Muon<<"|";  
        }
    cout<<"\n  =======================================================================";    
}
int KT_TTSach(char ms[8])//Ham kiem tra tinh trang sach truoc luc cho muon
{
    int i ;
    i=1 ;
    while((i<=n)&& (strcmp(a[i].Ma_Sach,ms)!=0))
        i++;   
    if (i>n)
        return 0 ; 
    if(a[i].SL_HienTai==0)
        return -1; 
    return i ;
}
void ThemCTPM(DS_CTPM c,int &k,int SL_Sach,char MSPhieu[10])
{
    int x;
    for(int i=1 ;i<=SL_Sach ;i++)
    {
        k++;
nhaplaisach:   
        cout<<" Nhap Vao Ma So Sach: ";
        cin>>c[k].Ma_Sach ;
        x=KT_TTSach(c[k].Ma_Sach);
        if (x==0)
        {
            cout<<" Ma Sach Nay Khong Co\n" ;
            goto nhaplaisach;
        }  
        else if (x==-1)
        {
            cout<<" Sach Nay Da Cho Muon Het\n";
            goto nhaplaisach;
        }
        else
        {
            strcpy(c[k].Ma_Phieu,MSPhieu);
            c[k].Tra=false ;
            cout<<" Nhap Vao Tinh Trang Cuon Sach: ";
            cin.ignore();
            gets(c[k].Tinh_Trang_Sach);
            a[x].SL_HienTai--;
            a[x].So_Lan_Muon++;
        }          
    }
}
void InCTPM(DS_CTPM c ,int k ,char MSPhieu[10])
{
        cout<<"\n \n                     CAC SACH TRONG PHIEU MUON " ;
        cout<<"\n    ===================================================================";
        cout<<"\n    |Ma Sach |               Tinh Trang                      |  Tra   |";
        cout<<"\n    ===================================================================";
        for(int i=1;i<=k;i++)
            if(strcmp(c[i].Ma_Phieu,MSPhieu)==0)
            {
                cout<<"\n    |"<<c[i].Ma_Sach<<setw(8-strlen(c[i].Ma_Sach)+1)<<"|"<<c[i].Tinh_Trang_Sach<<setw(47-strlen(c[i].Tinh_Trang_Sach)+1)<<"|"<<setw(8);
                if(c[i].Tra==false)cout<<"Chua Tra";else  cout<<"Da Tra";
                cout<<"|";
            }  
        cout<<"\n    ===================================================================";  
}
void XoaCTPM(DS_CTPM c,int &k,char MSPhieu[10])
{
    int vitrisach;
    int ViTri,dem=0;
    for(int i=1;i<=k;i++)
        if(strcmp(c[i].Ma_Phieu,MSPhieu)==0 && c[i].Tra==false)
        {  
            ViTri=i;
            dem++;
            vitrisach=TimSach(a,n,c[i].Ma_Sach);
            a[vitrisach].SL_HienTai++;
        }
    ViTri=ViTri-dem+1;
    for(int i=ViTri;i<=k;i++)
        c[i]=c[i+dem];
    k=k-dem;       
}  
void MuonSach()
{
    char msphieu[10];
    int slsach;
    int l;
    cout<<"\n                            MUON THEM SACH \n";
    cout<<"===============================================================================\n";
    cout<<"\n \n \n Nhap Vao Ma So Phieu Can Muon Sach: ";
    cin>>msphieu;
    l=TimMSPhieu(b,m,msphieu);
    if (l!=0)
    {
        InChiTietPhieu(b ,m,msphieu);
        cout<<"\n Nhap Vao So Luong Sach Ban Can Muon: ";
        cin>>slsach;
        ThemCTPM(c,k,slsach,b[l].Ma_Phieu);
        b[l].SL_Sach=b[l].SL_Sach+slsach;
        cout<<"\n MUON SACH THANH CONG ";
    }  
    else
        cout<<"\n KHONG CO THONG TIN MA SO PHIEU NAY ";
}      
void TraSach()
{
    char msphieu[10],mssach[8];
    cout<<"\n                         TRA SACH \n";
    cout<<"===============================================================================\n";
    cout<<" Nhap Vao Ma So Phieu: ";
    cin>>msphieu;
    if (TimMSPhieu(b,m,msphieu)==0)
        cout<<" KHONG CO THONG TIN MA SO PHIEU NAY";
    else
    {
        InChiTietPhieu(b ,m,msphieu);
        int soluongsach=b[TimMSPhieu(b,n,msphieu)].SL_Sach;
        int i ,dem=0,slsachtra;
        for(int j=1;j<=k;j++)       //tinh so luong sach chua tra cua phieu muon
        {
            if(c[j].Tra==false && strcmp(c[j].Ma_Phieu,msphieu)==0)
                dem++;
        }
        do
        {
            cout<<"\n Nhap Vao So Luong Sach Ban Muon Tra: ";
            cin>>slsachtra;
            if(slsachtra>dem)
                cout<<" So Luong Sach Ban Muon Tra Lon Hon So Luong Sach Ban Muon\n";
        }  
        while(slsachtra>dem);
        for(int j=1;j<=slsachtra;j++)
        {
            cout<<"\n Nhap Ma So Sach Ban Muon Tra: ";
            cin>>mssach;
            if(TimSach(a ,n ,mssach)==0)
                cout<<" Khong Co Thong Tin Ma So Sach Nay";
            else
            {
                for(i=0;i<=k;i++)
                {  
                    if(strcmp(c[i].Ma_Phieu,msphieu)==0 &&strcmp(c[i].Ma_Sach,mssach)==0 && c[i].Tra==false)
                    {
                        a[TimSach(a ,n ,mssach)].SL_HienTai++;
                        c[i].Tra=true;
                        break ;
                    }  
                }
                if(i>k)
                    cout<<"\n Tra Cuon Sach Nay Ko Thanh Cong, Vui Long Xem Lai Thong Tin Ban Da Nhap vao ";
                else
                    cout<<"\n Tra Sach Thanh Cong ";  
            }
        }      
    }          
}      
//===================== HAM TIM MA SO CUA PHIEU MUON SACH ================
int TimMSPhieu(DS_Phieu b ,int m ,char c[10])
{
    int i ;
    i=1 ;
    while((i<=m)&& (strcmp(b[i].Ma_Phieu,c)!=0))
        i++;   
    if (i>m) return 0 ;
    else return i ;
}
//====================== HAM THEM MOT PHIEU MUON SACH MOI =================================
void ThemPhieu(DS_Phieu b ,int &m)
{
    m++;
    int mssach ,Ngay,Thang,Nam;
    cout<<"\n                         THEM MOT PHIEU MUON MOI  \n";
    cout<<"===============================================================================\n";
nhaplaimaphieu: cout<<" Nhap Vao Ma Phieu: " ;
    cin>>b[m].Ma_Phieu;
   
    if (TimMSPhieu(b ,m-1 ,b[m].Ma_Phieu)!=0)
    {
        cout<<" Ma So Phieu Da Co, Vui Long Nhap Lai \n";
        goto nhaplaimaphieu ;
    }  
    cout<<" Nhap Vao Ho va Ten: " ;
    cin.ignore();
    gets(b[m].Ho_Ten);
NhapNgay:
    cout<<("\n NHAP NGAY THANG NAM MUON SACH \n");
    cout<<(" NGAY  : ");
    cin>>Ngay;
    cout<<(" THANG : ");
    cin>>Thang;
    cout<<(" NAM   : ");
    cin>>Nam;
    if(Ngay>0 && Ngay<KiemTraThang(Thang,Nam) && Thang>0 
    && Thang<=12 && Nam>0)
    {
        b[m].Ngay_Muon.Ngay=Ngay;
        b[m].Ngay_Muon.Thang=Thang;
        b[m].Ngay_Muon.Nam=Nam;
    }
    else
    {
        system("cls");
        cout<<("\n BAN DA NHAP SAI NGAY THANG \n\n");
        cout<<("\n XIN MOI NHAP LAI \n\n");
        goto NhapNgay;
    };
    cout<<" Nhap Vao So Luong Sach ";
    cin>>b[m].SL_Sach ;
    ThemCTPM(c,k,b[m].SL_Sach,b[m].Ma_Phieu);
 
    cout<<"\n THEM PHIEU MUON SACH THANH CONG \n";
}
//=================== HAM SUA THONG TIN PHIEU MUON SACH ====================
void SuaPhieu(DS_Phieu b ,int m)
{
        int msphieu ;
        char ms[8];
        int mssach ,Ngay,Thang,Nam;
    cout<<"\n                         SUA THONG TIN PHIEU MUON SACH  \n";
    cout<<"===============================================================================\n";
    cout<<"\n Nhap Vao Ma Phieu Can Sua Thong Tin: " ;
    cin>>ms;
    msphieu=TimMSPhieu(b ,m ,ms) ;
    if (msphieu==0)
        cout<<" Ma Phieu Khong Co \n";
    else
    {  
        cout<<" Nhap Vao Ho Ten: " ;
        cin.ignore();
        gets(b[msphieu].Ho_Ten);
NhapNgay:
        cout<<(" NHAP NGAY THANG NAM MUON SACH  \n");
        cout<<(" NGAY  : ");
        cin>>Ngay;
        cout<<(" THANG : ");
        cin>>Thang;
        cout<<(" NAM   : ");
        cin>>Nam;
        if(Ngay>0 && Ngay<KiemTraThang(Thang,Nam) && Thang>0 && Thang<=12 && Nam>0)
        {
            b[msphieu].Ngay_Muon.Ngay=Ngay;
            b[msphieu].Ngay_Muon.Thang=Thang;
            b[msphieu].Ngay_Muon.Nam=Nam;
        }
        else
        {
            system("cls");
            cout<<("\n BAN DA NHAP SAI NGAY THANG \n\n");
            cout<<("\n XIN MOI NHAP LAI \n\n");
            goto NhapNgay;
        }
        XoaCTPM(c,k,b[msphieu].Ma_Phieu);
        cout<<" Nhap Vao So Luong Sach ";
        cin>>b[msphieu].SL_Sach ;
        ThemCTPM(c,k,b[msphieu].SL_Sach,b[msphieu].Ma_Phieu);
    }  
}
//==================== HAM XOA THONG TIN MOT PHIEU MUON SACH =================
void XoaPhieu(DS_Phieu b ,int &m)
{
    int vitriphieu ;
    char ms[10];
    int mssach ;
    cout<<"\n                        XOA THONG TIN PHIEU MUON SACH \n";
    cout<<"===============================================================================\n";
    cout<<" Nhap Vao Ma Phieu Can Xoa Thong Tin: " ;
    cin>>ms;
    vitriphieu=TimMSPhieu(b ,m ,ms) ;
    if (vitriphieu==0)
        cout<<" Khong Tim Thay Ma Phieu \n";
    else
    {
        XoaCTPM(c,k,b[vitriphieu].Ma_Phieu);
        for(int j=vitriphieu;j<m;j++)
            b[j]=b[j+1];
        m--;
        cout<<" XOA THONG TIN PHIEU THANH CONG \n";
    }
}
//===================== HAM IN DANH SACH CAC PHIEU MUON SACH =========================
void InDanhSachPhieu(DS_Phieu b,int m)
{
        cout<<"\n                   DANH SACH CAC PHIEU MUON SACH ";   
        cout<<"\n      ========================================================";
        cout<<"\n      |    MP    |    Ho Va Ten      |  Ngay Muon | So Luong |";
        cout<<"\n      ========================================================";
        for(int i=1;i<=m;i++)
            cout<<"\n      |"<<b[i].Ma_Phieu<<setw(10-strlen(b[i].Ma_Phieu)+1)<<"|"
            <<b[i].Ho_Ten<<setw(19-strlen(b[i].Ho_Ten)+1)<<"|"
            <<setw(4)<<b[i].Ngay_Muon.Ngay<<"-"<<setw(2)<<b[i].Ngay_Muon.Thang<<"-"
            <<b[i].Ngay_Muon.Nam<<"|"<<setw(10)<<b[i].SL_Sach<<"|";
        cout<<"\n      ========================================================";
}
//====================== HAM THONG KE CAC PHIEU MUON SACH QUA HAN ============================
void InPhieuMuonQuaHan(DS_Phieu b,int m)
{
    int Ngay,Thang,Nam,SoNgay ;
    char chuoingay[2],chuoithang[2],chuoinam[4];
     tm *today ;
    time_t ltime;
    time( &ltime );
    today = localtime( &ltime );
    Ngay=today->tm_mday;
    Thang=today->tm_mon+1;
    Nam=today->tm_year+1900;
    cout<<"\n                     HOM NAY LA :"<<Ngay<<"-"<<Thang<<"-"<<Nam<<endl;
    cout<<"\n             DANH SACH CAC PHIEU MUON SACH QUA HAN    ";
    cout<<"\n      ========================================================";
    cout<<"\n      |    MP    |    Ho Va Ten      |  Ngay Muon | So Luong |";
    cout<<"\n      ========================================================";
    for(int i=1;i<=m;i++)
    {
        if(b[i].Ngay_Muon.Nam==Nam)
        {
            SoNgay=ViTri(Ngay,Thang,Nam)-ViTri(b[i].Ngay_Muon.Ngay,b[i].Ngay_Muon.Thang,b[i].Ngay_Muon.Nam);
        }
        else if(b[i].Ngay_Muon.Nam!=Nam)
        {
            SoNgay=NamNhuan(b[i].Ngay_Muon.Nam)-ViTri(b[i].Ngay_Muon.Ngay,b[i].Ngay_Muon.Thang,b[i].Ngay_Muon.Nam)+1+ViTri(Ngay,Thang,Nam);
        }
        int consach=0;
        for(int j=1;j<=k;j++)
        {
            if(strcmp(c[j].Ma_Phieu,b[i].Ma_Phieu)==0 && c[j].Tra==false)
            {
                consach=1;
                break;
            }
        }
        if(SoNgay>=30 && consach==1)
            cout<<"\n      |"<<b[i].Ma_Phieu<<setw(10-strlen(b[i].Ma_Phieu)+1)<<"|"
            <<b[i].Ho_Ten<<setw(19-strlen(b[i].Ho_Ten)+1)<<"|"
            <<setw(4)<<b[i].Ngay_Muon.Ngay<<"-"<<setw(2)<<b[i].Ngay_Muon.Thang<<"-"
            <<b[i].Ngay_Muon.Nam<<"|"<<setw(10)<<b[i].SL_Sach<<"|";
    }
    cout<<"\n      ========================================================";              
       
}
//================================== HAM IN THONG TIN CHI TIET MOT PHIEU MUON SACH ======================
void InChiTietPhieu(DS_Phieu b ,int m,char ms[8])
{
    int ViTri ;
        cout<<"\n                THONG TIN CHI TIET PHIEU MUON SACH \n";
    cout<<"===============================================================================\n";
    ViTri=TimMSPhieu(b,m,ms);
    if (ViTri==0)
        cout<<" KHONG CO MA SO PHIEU NAY ";
    else
    {
        cout<<"\n      =========================================================";
        cout<<"\n      |    MP    |    Ho Va Ten      |  Ngay Muon | So Luong  |";
        cout<<"\n      =========================================================";
        cout<<"\n      |"<<b[ViTri].Ma_Phieu<<setw(10-strlen(b[ViTri].Ma_Phieu)+1)<<"|"<<b[ViTri].Ho_Ten<<setw(19-strlen(b[ViTri].Ho_Ten)+1)<<"|"<<setw(4)<<b[ViTri].Ngay_Muon.Ngay<<"-"<<setw(2)<<b[ViTri].Ngay_Muon.Thang<<"-"
                            <<b[ViTri].Ngay_Muon.Nam<<"|"<<setw(11)<<b[ViTri].SL_Sach<<"|";
        cout<<"\n      =========================================================";
        InCTPM(c,k,b[ViTri].Ma_Phieu);
    }  
}
void DocGiaMuonNhieu()
{
    DS_Phieu d ;
    PhieuMuon tam ;
    int h;
    for(int i=1;i<=m;i++)
    {
        d[i]=b[i];
    }
        
    int post;
    for(int i=2;i<=m;i++)
    {
        tam=d[i];
        post=i-1;
        while(post>=1 && d[post].SL_Sach>tam.SL_Sach)
            {d[post+1]=d[post];post--;}
        d[post+1]=tam; 
    }
    cout<<"\n            TOP 5 DOC GIA MUON SACH NHIEU TRONG THU VIEN ";
    cout<<"\n      =========================================================";
    cout<<"\n      |    MP    |    Ho Va Ten      |  Ngay Muon | So Luong  |";
    cout<<"\n      =========================================================";
    if(m>5) h=m-5;  
    else h=0;    
    for(int i=m;i>h;i--) //chi in ra 5 doc gia muon sach nhieu nhat
    {   
        if(d[i].SL_Sach!=0)
        {
        cout<<"\n      |"<<d[i].Ma_Phieu<<setw(10-strlen(d[i].Ma_Phieu)+1)<<"|"<<d[i].Ho_Ten
        <<setw(19-strlen(d[i].Ho_Ten)+1)<<"|"<<setw(4)<<d[i].Ngay_Muon.Ngay<<"-"<<setw(2)<<d[i].Ngay_Muon.Thang<<"-"
                            <<d[i].Ngay_Muon.Nam<<"|"<<setw(11)<<d[i].SL_Sach<<"|";
        }
    }  
    cout<<"\n      =========================================================";
}  
//================================================= HAM GHI DU LIEU RA FILE ========================
void GhiDuLieu(DS_Sach a,DS_Phieu b ,DS_CTPM c,int n ,int m,int k)
{
    FILE *f ;
    f=fopen("data1.txt","wb");
    fwrite(&n,sizeof(int),1,f);
    fwrite(&m,sizeof(int),1,f);
    fwrite(&k,sizeof(int),1,f);
    for(int i=1;i<=n;i++)
        fwrite(&a[i],sizeof(Sach),1,f);
    for (int j=1;j<=m;j++)
        fwrite(&b[j],sizeof(PhieuMuon),1,f);
    for (int x=1;x<=k;x++)
        fwrite(&c[x],sizeof(CTPM),1,f);    
    fclose(f) ;
    cout<<"\n GHI DU LIEU VAO FILE THANH CONG \n"   ;
}
//==================================== HAM DOC DU LIEU TU FILE VAO DANH SACH ======================
void DocDuLieu(DS_Sach &a,DS_Phieu &b ,DS_CTPM &c,int &n ,int &m,int &k)
{
    FILE *f ;
    Sach g ;
    PhieuMuon d ;
    CTPM e ;
    f=fopen("data1.txt","rb");
    if (f==NULL )
        cout<<"\n                FILE DU LIEU KHONG TON TAI VUI LONG TAO MOI DANH SACH \n \n \n";
    else
    {  
        fread(&n,sizeof(int),1,f);
        fread(&m,sizeof(int),1,f);
        fread(&k,sizeof(int),1,f);
        for (int i=1;i<=n;i++)
        {
            fread(&g,sizeof(Sach),1,f);
            a[i]=g;
        }
        for (int j=1;j<=m;j++)
        {
            fread(&d,sizeof(PhieuMuon),1,f);
            b[j]=d;
        }
        for (int x=1;x<=k;x++)
        {
            fread(&e,sizeof(CTPM),1,f);
            c[x]=e;
        }
        fclose(f); 
    }
}

int Menu()
{
        int chon ;
        cout<<"\n     =======================================================================";
        cout<<"\n     |                Bai Tap Cau Truc Du Lieu Va Giai Thuat               |";          
        cout<<"\n     |                      CHUONG TRINH QUAN LY THU VIEN                  |";
        cout<<"\n     ***********************************************************************";
        cout<<"\n     |        Nhom sinh vien:          Huynh Khanh Duy - 19119081          |";
        cout<<"\n     |                                 Vo Hoai Bao     - 18119059          |";
        cout<<"\n     |                                 Dinh Nhat Khang - 19119099          |";
        cout<<"\n     ***********************************************************************";
        cout<<"\n     |                   CHUONG TRINH QUAN LY THU VIEN                     |";
        cout<<"\n     =======================================================================";
        cout<<"\n     |          QUAN LY SACH            |      QUAN LY PHIEU MUON          |";
        cout<<"\n     =======================================================================";
        cout<<"\n     |1.Cap Nhat Sach                   |5.Cap Nhat Phieu Muon             |";
        cout<<"\n     |2.In Thong Tin Tat Ca Sach        |6.In Thong Tin Tat Ca Phieu Muon  |";
        cout<<"\n     |3.Tim Thong Tin Sach              |7.Tim Thong Tin Phieu Muon        |"; 
        cout<<"\n     |4.Thong Ke Sach                   |8.Muon Sach                       |";
        cout<<"\n     |                                  |9.Tra Sach                        |";
        cout<<"\n     |                                  |10.Thong Ke Phieu Muon            |";
        cout<<"\n     |---------------------------------------------------------------------|";    
        cout<<"\n     |                      ---Nhan phim 0 de thoat---                     |";     
        cout<<"\n     ======================================================================="; 
        cout<<"\n                    Vui Long Chon Cac Phim Chuc Nang Tuong Ung: ";
        cin>>chon; 
        system("cls");
        return chon ;
}  
void Thoat()
{
    cout<<"\n \n \n ==============================================================================";
    cout<<"\n                       Nhan ENTER De Ra Menu Chinh \n ";
    getch();
    system("cls");
}
int CapNhatDS()
{
    int sel;
    while(1)
    {
        int sel;
        cout<<"\n   ===============================";
        cout<<"\n   |   Cap nhat thong tin sach   |";
        cout<<"\n   |-----------------------------|";
        cout<<"\n   |   1.Them Sach Moi           |";
        cout<<"\n   |   2.Sua Thong Tin Sach      |";
        cout<<"\n   |   3.Xoa Thong Tin Sach      |";
        cout<<"\n   |   4.Quay ve Menu chinh      |";
        cout<<"\n   ==============================|";
        cout<<"\n          Nhap lua chon: ";
        cin>>sel;
        //system("cls");
        switch(sel)
        {
            case 1 : InToanBoSach(a,n); cout<<endl<<endl; ThemSach(a,n)  ;Thoat() ;break ;
            case 2 : InToanBoSach(a,n); cout<<endl<<endl; SuaSach(a,n) ;Thoat() ;break ;
            case 3 : InToanBoSach(a,n); cout<<endl<<endl; XoaSach(a,n) ;Thoat() ;break ;
            case 4 : return 0;Menu(); break;
        }
    }  
}

int CapNhatPhieu()
{
    int sel;
    while(1)
    {
        int sel;
        cout<<"\n   ===============================";
        cout<<"\n   |   Cap nhat thong tin phieu  |";
        cout<<"\n   |-----------------------------|";
        cout<<"\n   |   1.Them Phieu Moi          |";
        cout<<"\n   |   2.Sua Thong Tin Phieu     |";
        cout<<"\n   |   3.Xoa Thong Tin Phieu     |";
        cout<<"\n   |   4.Quay ve Menu chinh      |";
        cout<<"\n   ==============================|";
        cout<<"\n          Nhap lua chon: ";
        cin>>sel;
        //system("cls");
        switch(sel)
        {
            case 1 : InToanBoSach(a,n); cout<<endl<<endl; ThemPhieu(b,m); Thoat(); break;
            case 2 : InDanhSachPhieu(b,m); cout<<endl<<endl; SuaPhieu(b,m); Thoat(); break;
            case 3 : InDanhSachPhieu(b,m); cout<<endl<<endl; XoaPhieu(b,m); Thoat(); break;
            case 4 : return 0; Menu(); break;
        }
    }  
}
int ThongKeSach()
{
    int sel;
    while(1)
    {
        int sel;
        cout<<"\n   ===============================";
        cout<<"\n   |         Thong Ke Sach       |";
        cout<<"\n   |-----------------------------|";
        cout<<"\n   |   1.Theo The Loai           |";
        cout<<"\n   |   2.Da Cho Muon Het         |";
        cout<<"\n   |   3.Duoc Muon Nhieu Nhat    |";
        cout<<"\n   |   4.Quay ve Menu chinh      |";
        cout<<"\n   ==============================|";
        cout<<"\n          Nhap lua chon: ";
        cin>>sel;
        //system("cls");
        switch(sel)
        {
            case 1 : InToanBoSach(a,n); cout<<endl<<endl; TimSachTheLoai(a,n); Thoat(); break ;
            case 2 : InToanBoSach(a,n); cout<<endl<<endl; ThongKeSachHet(a,n); Thoat(); break ;
            case 3 : InToanBoSach(a,n); cout<<endl<<endl; ThongKeSachMuonNhieu(); Thoat(); break ;
            case 4 : return 0; Menu(); break;
        }
    }
}
int ThongKePhieuMuon()
{
    int sel;
    while(1)
    {
        int sel;
        cout<<"\n   ===============================";
        cout<<"\n   |       Thong Ke Phieu Muon   |";
        cout<<"\n   |-----------------------------|";
        cout<<"\n   |   1.Qua Han                 |";
        cout<<"\n   |   2.Doc Gia Muon Nhieu Nhat |";
        cout<<"\n   |   3.Quay ve Menu chinh      |";
        cout<<"\n   ==============================|";
        cout<<"\n          Nhap lua chon: ";
        cin>>sel;
        //system("cls");
        switch(sel)
        {
            case 1 : InDanhSachPhieu(b,m); cout<<endl<<endl; InPhieuMuonQuaHan(b,m); Thoat(); break;   
            case 2 : InDanhSachPhieu(b,m); cout<<endl<<endl; DocGiaMuonNhieu(); Thoat(); break;
            case 3 : return 0; Menu(); break;
        }
    }
}

//======================================================= HAM MAIN ====================================

int main()
{
    DocDuLieu(a,b,c,n,m,k);
    int chon ;
    char ms[8];
    while (1)
    {
        chon=Menu();
        switch (chon)
        {
            case 0  :goto exit ; break;
            case 1  :CapNhatDS(); break;
            case 2  :InToanBoSach(a,n); Thoat(); break;
            case 3  :
                cout<<"Nhap Vao Ma So Sach Can Xem Thong Tin \n ";
                cin>>ms;
                InChiTietSach(a,n,ms); Thoat(); break;
            case 4  :ThongKeSach(); break;
            case 5  :CapNhatPhieu(); break;
            case 6  :InDanhSachPhieu(b,m);Thoat()  ;break ;
            case 7  :
                cout<<"Nhap Vao Ma So Cua Phieu Can Xem Thong Tin Chi Tiet: " ;
                cin>>ms ;
                InChiTietPhieu(b,m,ms) ;Thoat(); break ;
            case 8  :InDanhSachPhieu(b,m); InToanBoSach(a,n); cout<<endl<<endl; MuonSach(); Thoat(); break ;
            case 9  :TraSach(); Thoat(); break ;
            case 10 :ThongKePhieuMuon(); break ;
            default :goto exit;break;
        }
    }
exit:   cout << "\nBAN CO MUON LUU DU LIEU VAO FILE KHONG ? - Y/N \n";
        int ch=getch();
        if (toupper(ch)=='Y')
            GhiDuLieu(a,b,c,n,m,k);
}