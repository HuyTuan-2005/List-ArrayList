#ifndef _List_ArrayList_h
#define _List_ArrayList_h

//Phan khai bao thu vien
#include <stdio.h>
#include <iostream>

//==============================================================
//Phan khai bao cac kieu du lieu
struct Package					// Dinh nghia cua 1 goi hang
{
	int packageID;				// Mã số của gói hàng
	char senderName[100];		// Tên người gửi
	char senderAddress[100];	// Địa chỉ người gửi
	char senderPhone[20];		// Số điện thoại người gửi

	char receiverName[100];		// Tên người nhận 
	char receiverAddress[100];  // Địa chỉ người nhận
	char receiverPhone[20];		// Số điện thoại người nhận

	double shippingFee;			// Phí vận chuyển gói hàng
	double packageWeight;		// Trọng lượng của gói hàng (kg)
	char packageType[20];		// Loại hàng hóa
};
//--------------------------------------------------------------
typedef Package DataType; 		// Khai bao 1 kieu du lieu nguoi dung
//--------------------------------------------------------------
struct SNode
{
	DataType Data;				// Luu thong tin cua 1 Node
	SNode *Next;				// Luu con tro den Node ke sau (neu co)
};
//--------------------------------------------------------------
struct SList
{
	SNode *Head;				// Luu con tro den Node dau danh sach
	SNode *Tail;				// Luu con tro den Node cuoi danh sach
};
//==============================================================
//Phan khai bao cac nguyen mau ham
void inputPackageInfo(DataType &x);		// Nhap thong tin cua 1 goi hang
SNode *createSNode(DataType x);			// Cap phat 1 node moi

void initSList(SList &sl);				// Lam rong danh sach
int isEmpty(SList sl);					// Kiem tra danh sach co rong hay khong?

int insertHead(SList &sl, DataType x);	// Them 1 node moi vao dau danh sach
int insertTail(SList &sl, DataType x);  // Them 1 node moi vao cuoi danh sach
int insertAfter(SList &sl, DataType x);

int deleteHead(SList &sl, DataType &x); // Xoa 1 node o dau danh sach
int deleteTail(SList &sl, DataType &x); // Xoa 1 node o cuoi danh sach

void showPackage(DataType x);			// Hien thi thong tin cua 1 goi hang
void printPackages(SList sl);			// Hien thi thong tin danh sach cac goi hang

void inputPackageList(SList &sl);		// Nhap thong tin cac goi hang tu ban phim
void loadPackageFILE(FILE *fi, DataType &x); //Load  thong tin cac goi hang tu file.txt
void inputPackageList_FILE(SList &sl, char filename[]);

void Menu();
void Process();


#endif _List_ArrayList_h

