#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUMBER_OF_DATA 9

FILE *f;

struct Date{
	int day, month, year;
};

struct FootballPlayer{
	char name[30];
	Date birthDay;
	int age;
	float height;
	int shirtNumber;
	char role[10];
	char nation[30];
	char dominantFoot[3];
};

void deleteExtraCharacter(char x[]){
	size_t len = strlen(x);
	for(int i=0; i < len; i++){
		x[i]=x[i+1];
	}
	x[len-1] = '\0';	
}
 
int countPlayer(FootballPlayer playerList[], int &number_of_player){
	number_of_player = 0;
	while(fscanf(f,"%[^;];%d;%d;%d;%f;%d;%[^;];%[^;];%s",playerList[number_of_player].name,&playerList[number_of_player].birthDay.day,&playerList[number_of_player].birthDay.month,
				&playerList[number_of_player].birthDay.year,&playerList[number_of_player].height,&playerList[number_of_player].shirtNumber,playerList[number_of_player].role,
				playerList[number_of_player].nation,playerList[number_of_player].dominantFoot) == NUMBER_OF_DATA){
					number_of_player++;								
	}
	return number_of_player;
}

void printMenu(){
	printf("v1.0.1\n");
	printf("--------QUAN LY CAU THU BONG DA--------\n");
	printf("------------YOUNG BOYS FC--------------\n");
	printf("Danh sach thao tac: \n");
	printf("1 - Xuat danh sach cau thu.\n");
	printf("2 - Them cau thu moi.\n");
	printf("3 - Xoa cau thu.\n");
	printf("4 - Chinh sua thong tin cau thu.\n");
	printf("5 - Sap xep.\n");
	printf("6 - Tim kiem cau thu.\n");
	printf("0 - Thoat!\n");
	printf("Nhap lua chon: ");
}

void printTitle(){
	printf("+-----+------------------------------+------------+------+-----------+-------+----------+--------------+------------+\n");
	printf("| %-3s | %-29s| %-10s | %-4s | %-6s | %-5s | %-8s | %-12s | %-9s |\n","STT","Ho ten","Ngay sinh","Tuoi","Chieu cao",
				"So ao","Vi tri","Quoc tich","Chan thuan");
		printf("+-----+------------------------------+------------+------+-----------+-------+----------+--------------+------------+\n");
}

void listPlayer(FootballPlayer playerList[], int number_of_player){
	
	time_t now = time(0);
	struct tm *local_time = localtime(&now);
	int current_year = local_time->tm_year + 1900;
	int STT = 1;
	for(int i=0; i<number_of_player; i++){
		playerList[i].age = current_year - playerList[i].birthDay.year;
		deleteExtraCharacter(playerList[i].name);
		printf("|  %-d  | %-29s| %02d/%02d/%04d |  %-3d |   %-5.2fm  |  %2d   | %-8s | %-12s |     %-7s|\n",
		STT,playerList[i].name,playerList[i].birthDay.day,playerList[i].birthDay.month,playerList[i].birthDay.year,
		playerList[i].age,playerList[i].height,playerList[i].shirtNumber,playerList[i].role,playerList[i].nation,playerList[i].dominantFoot);
		STT++;
	}
	printf("+-----+------------------------------+------------+------+-----------+-------+----------+--------------+------------+\n");	
}

void addNewPlayer(FootballPlayer playerList[], int &number_of_player){
	f = fopen("data.txt","a+");
	if(f==NULL)
		printf("Error opening file!\n");
	number_of_player++;
	printf("\nNhap ten cau thu: ");fflush(stdin);
	gets(playerList[number_of_player].name);
	printf("\nNhap ngay thang nam sinh (DD MM YYYY): ");
	scanf("%d %d %d",&playerList[number_of_player].birthDay.day,&playerList[number_of_player].birthDay.month,
																&playerList[number_of_player].birthDay.year);
	printf("\nNhap chieu cao: ");
	scanf("%f",&playerList[number_of_player].height);
	printf("\nNhap so ao: ");
	scanf("%d",&playerList[number_of_player].shirtNumber);
	printf("\nNhap vi tri: ");fflush(stdin);
	gets(playerList[number_of_player].role);
	printf("\nNhap quoc tich: ");fflush(stdin);
	gets(playerList[number_of_player].nation);
	printf("\nNhap chan thuan: ");fflush(stdin);
	gets(playerList[number_of_player].dominantFoot);
	
	fprintf(f,"\n%s;%02d;%02d;%04d;%.2f;%d;%s;%s;%s",playerList[number_of_player].name,playerList[number_of_player].birthDay.day,
	playerList[number_of_player].birthDay.month,playerList[number_of_player].birthDay.year,playerList[number_of_player].height,
	playerList[number_of_player].shirtNumber,playerList[number_of_player].role,playerList[number_of_player].nation,playerList[number_of_player].dominantFoot);
	fclose(f);
	printf("\n-----------------------\n");	
	printf("Da them cau thu moi thanh cong!");
	printf("\n-----------------------------\n");
}

void deletePlayer(FootballPlayer playerList[], int &number_of_player, int shirtNumber){
	FILE *temp = fopen("temp.txt","w");
	if(temp == NULL){
		printf("Error opening file!\n");
		return;
	}
	int found = 0;	
	rewind(f);
	for(int i=0; i<number_of_player; i++){
									
		if(playerList[i].shirtNumber != shirtNumber){
			deleteExtraCharacter(playerList[i].name);
			fprintf(temp,"\n%s;%02d;%02d;%04d;%.2f;%d;%s;%s;%s",playerList[i].name,playerList[i].birthDay.day,
			playerList[i].birthDay.month,playerList[i].birthDay.year,playerList[i].height,
			playerList[i].shirtNumber,playerList[i].role,playerList[i].nation,playerList[i].dominantFoot);
			
		}
		else{
			found = 1;
		}
	}
	
	if(found){
    	number_of_player--;
    	fclose(f);
   		fclose(temp);
   		remove("data.txt");
   		rename("temp.txt","data.txt");
   		printf("\nXoa cau thu thanh cong!\n");
	} 
		
    else{
    	printf("\nKhong tim thay cau thu voi so ao %d.\n", shirtNumber);
    	fclose(f);
   		fclose(temp);
   		remove("temp.txt");
	}
    f = fopen("data.txt","r+");
}

void changePlayerData(FootballPlayer playerList[], int number_of_player, int shirtNumber){
	FILE *temp = fopen("temp.txt","w");
	if(temp == NULL){
		printf("Error opening file!\n");
		return;
	}
	int found = 0;	
	rewind(f);
	for(int i=0; i<number_of_player; i++){
									
		if(playerList[i].shirtNumber == shirtNumber){
			found = 1;
			printf("\nNhap ten cau thu moi: ");fflush(stdin);
			gets(playerList[i].name);
			printf("\nNhap ngay thang nam sinh moi (DD MM YYYY): ");
			scanf("%d %d %d",&playerList[i].birthDay.day,&playerList[i].birthDay.month,
											&playerList[i].birthDay.year);
			printf("\nNhap chieu cao moi: ");
			scanf("%f",&playerList[i].height);
			printf("\nNhap so ao moi: ");
			scanf("%d",&playerList[i].shirtNumber);
			printf("\nNhap vi tri moi: ");fflush(stdin);
			gets(playerList[i].role);
			printf("\nNhap quoc tich moi: ");fflush(stdin);
			gets(playerList[i].nation);
			printf("\nNhap chan thuan moi: ");fflush(stdin);
			gets(playerList[i].dominantFoot);	
		}
		else{
			deleteExtraCharacter(playerList[i].name);
		}
		fprintf(temp,"\n%s;%02d;%02d;%04d;%.2f;%d;%s;%s;%s",playerList[i].name,playerList[i].birthDay.day,
		playerList[i].birthDay.month,playerList[i].birthDay.year,playerList[i].height,
		playerList[i].shirtNumber,playerList[i].role,playerList[i].nation,playerList[i].dominantFoot);
	}
	
	if(!found){
		printf("\nKhong tim thay cau thu voi so ao %d.\n", shirtNumber);
    	fclose(f);
   		fclose(temp);
   		remove("temp.txt");
	}
    else{
    	fclose(f);
   		fclose(temp);
   		remove("data.txt");
   		rename("temp.txt","data.txt");
		printf("\nCap nhat du lieu thanh cong!\n");
	}
    f = fopen("data.txt","r+");
}

void increaseShirtNumber(FootballPlayer playerList[], int number_of_player){
	for(int i=0; i<number_of_player-1; i++){
		for(int j=i+1; j<number_of_player; j++){
			if(playerList[i].shirtNumber > playerList[j].shirtNumber){
				FootballPlayer temp = playerList[i];
				playerList[i] = playerList[j];
				playerList[j] = temp;
			}
		}
	}
	listPlayer(playerList, number_of_player);
}

void increaseName(FootballPlayer playerList[], int number_of_player){
	for(int i=0; i<number_of_player-1; i++){
		for(int j=i+1; j<number_of_player; j++){
			if(stricmp(playerList[i].name,playerList[j].name)>0){
				FootballPlayer temp = playerList[i];
				playerList[i] = playerList[j];
				playerList[j] = temp;
			}
		}
	}
	listPlayer(playerList, number_of_player);
}

void findName(FootballPlayer playerList[], int number_of_player, char findingName[]){
	time_t now = time(0);
	struct tm *local_time = localtime(&now);
	int current_year = local_time->tm_year + 1900;
	int STT = 1;		
	for(int i=0; i<number_of_player; i++){
		if(strstr(playerList[i].name,findingName)){
			playerList[i].age = current_year - playerList[i].birthDay.year;
			deleteExtraCharacter(playerList[i].name);
			printf("|  %-d  | %-29s| %02d/%02d/%04d |  %-3d |   %-5.2fm  |  %2d   | %-8s | %-12s |     %-7s|\n",
			STT,playerList[i].name,playerList[i].birthDay.day,playerList[i].birthDay.month,playerList[i].birthDay.year,
			playerList[i].age,playerList[i].height,playerList[i].shirtNumber,playerList[i].role,playerList[i].nation,playerList[i].dominantFoot);	
			STT++;
		}
	}
	printf("+-----+------------------------------+------------+------+-----------+-------+----------+--------------+------------+\n");
}

int main()
{
	struct FootballPlayer playerList[50];
	int choose;
	do{
		f = fopen("data.txt","r+");
			if(f == NULL)
				printf("Error opening file!");
		printMenu();
		scanf("%d",&choose);
		int number_of_player;
		switch(choose){
			case 0:
				printf("XIN CHAO VA HEN GAP LAI!");
				break;
			case 1:
				printf("\n[1] - Danh sach cac cau thu.\n");
				printTitle();
				number_of_player = countPlayer(playerList, number_of_player);
				listPlayer(playerList, number_of_player);
				fclose(f);
				system("pause");
				system("cls");
				break;
			case 2:
				printf("\n[2] - Them cau thu moi.\n");
				printf("-----------------------\n");
				number_of_player = countPlayer(playerList, number_of_player);
				addNewPlayer(playerList, number_of_player);
				system("pause");
				system("cls");
				break;
			case 3:
				printf("\n[3] - Xoa cau thu.\n");
				printf("------------------\n");
				int deleteShirtNumber;
				printf("Nhap so ao cua cau thu muon xoa: ");
				scanf("%d",&deleteShirtNumber);
				number_of_player = countPlayer(playerList, number_of_player);
				deletePlayer(playerList, number_of_player, deleteShirtNumber);
				system("pause");
				system("cls");
				break;
			case 4:
				printf("\n[4] - Chinh sua thong tin cau thu.\n");
				printf("----------------------------------\n");
				int changeShirtNumber;
				printf("Nhap so ao cua cau thu muon chinh sua: ");
				scanf("%d",&changeShirtNumber);
				number_of_player = countPlayer(playerList, number_of_player);
				changePlayerData(playerList, number_of_player, changeShirtNumber);
				system("pause");
				system("cls");
				break;
			case 5:
				int sortChoose;
				printf("\n[5] - Sap xep.\n");
				printf("--------------\n");
				printf("\t1 - Sap xep so ao theo thu tu tang dan.\n");
				printf("\t2 - Sap xep ten theo thu tu ABC.\n");
				printf("\tNhap lua chon: ");
				scanf("%d",&sortChoose);
				switch(sortChoose)
				{
					case 1:
						printf("\n[1] - Danh sach cac cau thu theo thu tu so ao tang dan.\n");
						printTitle();
						number_of_player = countPlayer(playerList, number_of_player);
						increaseShirtNumber(playerList, number_of_player);
						fclose(f);
						system("pause");
						system("cls");
						break;
					case 2:
						printf("\n[2] - Danh sach cac cau thu theo thu tu ABC.\n");
						printTitle();
						number_of_player = countPlayer(playerList, number_of_player);
						increaseName(playerList, number_of_player);
						fclose(f);
						system("pause");
						system("cls");
						break;
				}
				system("cls");
				break;
			case 6:
				char findingName[30];
				printf("\n[6] - Tim kiem cau thu.\n");
				printf("-----------------------\n");
				printf("Nhap ki tu hoac ten can tim: ");fflush(stdin);
				gets(findingName);
				printTitle();
				number_of_player = countPlayer(playerList, number_of_player);
				findName(playerList, number_of_player, findingName);
				system("pause");
				system("cls");
				break;
		}	
	}
	while(choose!=0);
	return 0;
}
