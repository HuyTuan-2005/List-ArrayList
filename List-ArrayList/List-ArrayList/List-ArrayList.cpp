#include "List-ArrayList.h"

//==============================================================
int main()
{
	Process();
}
//==============================================================
//--------------------------------------------------------------
void Menu()
{
	printf("\n======================================================");
	printf("\n1. Lam rong danh sach.");
	printf("\n2. Them n goi hang nhap tu ban phim.");
	printf("\n3. Them goi hang load tu file.");
	printf("\n4. In danh sach goi hang.");
	printf("\n5. Xoa dau danh sach.");
	printf("\n6. Xoa cuoi danh sach.");
	printf("\n0. Thoat khoi chuong trinh.");
	printf("\n======================================================\n");
	printf("\t-> Lua chon cua ban la: ");
}
//--------------------------------------------------------------
void Process()
{
	SList SL; initSList(SL);
	DataType x;
	int Choose;
	char filename[] = "DSPackages.txt";
	do
	{
		Menu();
		scanf("%d", &Choose);

		switch (Choose)
		{
		case 0:
			break;
		case 1:
			initSList(SL);
			break;
		case 2:
			inputPackageList(SL);
			break;
		case 3:
			inputPackageList_FILE(SL, filename);
			break;
		case 4:
			printPackages(SL);
			break;
		case 5:
			deleteHead(SL, x);
			break;
		case 6:
			deleteTail(SL, x);
			break;

		default:
			printf("Khong co lua chon: %d\n", Choose);
		}

	} while (Choose);
}
//--------------------------------------------------------------
void inputPackageInfo(DataType &x)// Nhập thông tin từ người dùng
{
	printf("\nNhap ma so cua goi hang: ");
	scanf("%d", &x.packageID); getchar();
	printf("Nhap ten nguoi gui: ");
	gets(x.senderName);
	printf("Nhap dia chi nguoi gui: ");
	gets(x.senderAddress);
	printf("Nhap so dien thoai nguoi gui: ");
	gets(x.senderPhone);

	printf("\nNhap ten nguoi nhan: ");
	gets(x.receiverName);
	printf("Nhap dia chi nguoi nhan: ");
	gets(x.receiverAddress);
	printf("Nhap so dien thoai nguoi nhan: ");
	gets(x.receiverPhone);

	printf("\nNhap phi van chuyen: ");
	scanf("%lf", &x.shippingFee);
	printf("Nhap trong luong goi hang (kg): ");
	scanf("%lf", &x.packageWeight);
	printf("Nhap loai hang: ");
	scanf("%s", x.packageType); getchar();
}
//--------------------------------------------------------------
SNode *createSNode(DataType x)
{
	SNode *newNode = new SNode();
	if (newNode)
	{
		newNode->Data = x;
		newNode->Next = NULL;
		return newNode;
	}
	return NULL;
}
//--------------------------------------------------------------
void initSList(SList &sl)
{
	sl.Head = sl.Tail = NULL;
}
//--------------------------------------------------------------
int isEmpty(SList sl)
{
	return sl.Head == NULL;
}
//--------------------------------------------------------------
int insertHead(SList &sl, DataType x)
{
	SNode *newNode = createSNode(x);
	if (newNode)
	{
		if (!isEmpty(sl))
		{
			newNode->Next = sl.Head;
			sl.Head = newNode;
		}
		else
			sl.Head = sl.Tail = newNode;
		return 1;
	}
	return 0;
}
//--------------------------------------------------------------
int insertTail(SList &sl, DataType x)
{
	SNode *newNode = createSNode(x);
	if (newNode)
	{
		if (!isEmpty(sl))
		{
			sl.Tail->Next = newNode;
			sl.Tail = newNode;
		}
		else
			sl.Head = sl.Tail = newNode;
		return 1;
	}
	return 0;
}
//--------------------------------------------------------------
int insertAfter(SList &sl, DataType x)
{
	return 1;// Chua lam
}
//--------------------------------------------------------------
int deleteHead(SList &sl, DataType &x)
{
	if (isEmpty(sl))
		return 0;

	SNode *tmp = sl.Head;
	sl.Head = sl.Head->Next;
	if (sl.Head == NULL)
		sl.Tail = NULL;
	x = tmp->Data;
	delete tmp;
	return 1;
}
//--------------------------------------------------------------
int deleteTail(SList &sl, DataType &x)
{
	if (isEmpty(sl))
		return 0;

	SNode *tmp = sl.Tail;
	SNode *p = sl.Head;

	if (sl.Head == sl.Tail)
		sl.Head = sl.Tail = NULL;
	else
	{
		while (p->Next != sl.Tail)
			p = p->Next;
		sl.Tail = p;
		sl.Tail->Next = NULL;
	}

	x = tmp->Data;
	delete tmp;
	return 1;
}
//--------------------------------------------------------------
void showPackage(DataType x)
{
	printf("%-15d%-20s%-20s%-15s%-20s%-20s%-15s%-15.3f%-20.2f%-15s\n",
		x.packageID, x.senderName, x.senderAddress,
		x.senderPhone, x.receiverName, x.receiverAddress,
		x.receiverPhone, x.shippingFee, x.packageWeight,
		x.packageType);
}
//--------------------------------------------------------------
void printPackages(SList sl)
{
	if (isEmpty(sl))
	{
		printf("Danh sach rong.");
		return;
	}
	int stt = 1;

	// pritnf("---");

	printf("\n%-5s%-15s%-20s%-20s%-15s%-20s%-20s%-15s%-15s%-20s%-15s\n",
		"STT",
		"PackageID", "SenderName", "SenderAddress", "SenderPhone",
		"ReceiverName", "ReceiverAddress", "ReceiverPhone",
		"ShippingFee", "PackageWeight", "PackageType");

	while (sl.Head)
	{
		printf("%-5d", stt++);
		showPackage(sl.Head->Data);
		sl.Head = sl.Head->Next;
	}
}
//--------------------------------------------------------------
void inputPackageList(SList &sl)
{
	int n;
	do
	{
		printf("Cho biet n goi hang can tao: ");
		scanf("%d", &n);
	} while (n <= 0);

	for (int i = 0; i < n; i++)
	{
		printf("\n------------------------------------");
		printf("\nNhap thong tin goi hang thu %d:\n", i + 1);
		DataType x;
		inputPackageInfo(x);
		insertTail(sl, x);
	}
}
//--------------------------------------------------------------
void inputPackageList_FILE(SList &sl, char filename[])
{
	FILE *fi = fopen(filename, "rt"); //readtext
	if (fi == NULL)
	{
		printf("Loi mo file: %s", filename);
		return;
	}

	DataType x;
	loadPackageFILE(fi, x);
	insertTail(sl, x);
	fclose(fi);
}
//--------------------------------------------------------------
void loadPackageFILE(FILE *fi, DataType &x) //Load  thong tin cac goi hang tu file.txt
{
	fscanf(fi, "%d%[^#]%*c%[^#]%*c%[^#]%*c%[^#]%*c%[^#]%*c%[^#]%*c%[^#]%*lf%[^#]%*lf%[^#]%*c\n",
		&x.packageID, &x.senderName, &x.senderAddress,
		&x.senderPhone, &x.receiverName, &x.receiverAddress,
		&x.receiverPhone, &x.shippingFee, &x.packageWeight,
		&x.packageType);
}
//--------------------------------------------------------------