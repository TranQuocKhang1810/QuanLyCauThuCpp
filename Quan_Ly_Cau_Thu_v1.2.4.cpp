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

struct playerLinkedList{
	FootballPlayer data;
	playerLinkedList *next;
};
typedef struct playerLinkedList *node;

void deleteExtraCharacter(char x[]){
	size_t len = strlen(x);
	for(int i=0; i < len; i++){
		x[i]=x[i+1];
	}
	x[len-1] = '\0';	
}

void uppercaseFirtsLetter(char x[]){
	size_t len = strlen(x);
	for(int i = 0; i < len; i++){
		if(i == 0 || (i > 0 && x[i-1] == 32))
			if(x[i] >= 97 && x[i] <= 122)
				x[i] = x[i] - 32;
	}
}

int currentYear(){
	time_t now = time(0);
	struct tm *local_time = localtime(&now);
	int current_year = local_time->tm_year + 1900;
	return current_year;
}

void printMenu(){
	printf("v1.2.4\n");
	printf("--------QUAN LY CAU THU BONG DA--------\n");
	printf("------------YOUNG BOYS FC--------------\n");
	printf("Danh sach thao tac: \n");
	printf("[1] - Xuat danh sach cau thu.\n");
	printf("[2] - Them cau thu moi.\n");
	printf("[3] - Xoa cau thu.\n");
	printf("[4] - Chinh sua thong tin cau thu.\n");
	printf("[5] - Sap xep.\n");
	printf("[6] - Tim kiem cau thu.\n");
	printf("[7] - Bo loc.\n");
	printf("[0] - Thoat!\n");
	printf("Nhap lua chon: ");
}

void printBoardLine(){
	printf("\t\t+------+------------------------------+------------+------+-----------+-------+----------+--------------+------------+\n");
}

void printTitle(){
	printBoardLine();
	printf("\t\t|  %-4s| %-29s| %-10s | %-4s | %-6s | %-5s | %-8s | %-12s | %-9s |\n",
	"STT","Ho ten","Ngay sinh","Tuoi","Chieu cao",
	"So ao","Vi tri","Quoc tich","Chan thuan");
	printBoardLine();
}

node initHead(){
	node head = NULL;
	return head;
}

node createNode(FootballPlayer player){
	node temp;
	temp = new playerLinkedList;
	temp->next = NULL;
	strcpy(temp->data.name,player.name);
	temp->data.birthDay.day = player.birthDay.day;
	temp->data.birthDay.month = player.birthDay.month;
	temp->data.birthDay.year = player.birthDay.year;
	temp->data.height = player.height;
	temp->data.shirtNumber = player.shirtNumber;
	strcpy(temp->data.role,player.role);
	strcpy(temp->data.nation,player.nation);
	strcpy(temp->data.dominantFoot,player.dominantFoot);
	return temp;
}

node addToList(node head, FootballPlayer player){
    node temp = createNode(player);
    if(head == NULL) {
        head = temp;
    } else {
        node p = head;
        while(p->next != NULL){
            p = p->next; 
        }
        p->next = temp;
    }
    return head;
}

node insertDataToNode(FootballPlayer player){
    node head = initHead();
    while(fscanf(f,"%[^;];%d;%d;%d;%f;%d;%[^;];%[^;];%s",player.name,&player.birthDay.day,&player.birthDay.month,
    &player.birthDay.year,&player.height,&player.shirtNumber,player.role,player.nation,player.dominantFoot) == NUMBER_OF_DATA){
        deleteExtraCharacter(player.name);
		head = addToList(head, player);							
    }
    fclose(f);
    return head;
}

void printPlayer(node p, int STT){
	p->data.age = currentYear() - p->data.birthDay.year;
	printf("\t\t|  %2d  | %-29s| %02d/%02d/%04d |  %-3d |   %-5.2fm  |  %2d   | %-8s | %-12s |     %-7s|\n",
	STT,p->data.name,p->data.birthDay.day,p->data.birthDay.month,p->data.birthDay.year,
	p->data.age,p->data.height,p->data.shirtNumber,p->data.role,p->data.nation,p->data.dominantFoot);
}

node addNewPlayer(FootballPlayer player, node head){
	
	printf("\nNhap ten cau thu: ");fflush(stdin);
	gets(player.name); uppercaseFirtsLetter(player.name);
	printf("\nNhap ngay thang nam sinh (DD MM YYYY): ");
	scanf("%d %d %d",&player.birthDay.day,
	&player.birthDay.month,
	&player.birthDay.year);
	printf("\nNhap chieu cao: ");
	scanf("%f",&player.height);
	printf("\nNhap so ao: ");
	scanf("%d",&player.shirtNumber);
	printf("\nNhap vi tri: ");fflush(stdin);
	gets(player.role);uppercaseFirtsLetter(player.role);
	printf("\nNhap quoc tich: ");fflush(stdin);
	gets(player.nation);uppercaseFirtsLetter(player.nation);
	printf("\nNhap chan thuan: ");fflush(stdin);
	gets(player.dominantFoot);uppercaseFirtsLetter(player.dominantFoot);
	
	head = addToList(head, player);
	
	printf("\n-----------------------------------\n");	
	printf("[!] - Da them cau thu moi thanh cong!");
	printf("\n-----------------------------------\n");
	system("pause");
	return head;
}

node deleteNode(node head, int shirtNumber){
    if(head->data.shirtNumber == shirtNumber) {
        node temp = head;
        head = head->next;
        delete temp;
    }
    else{
    	node current = head;
	    node prev = NULL;
	    while(current != NULL) {
	        if(current->data.shirtNumber == shirtNumber)
	            break;
	        prev = current;
	        current = current->next;
	    }
	    prev->next = current->next;
	    delete current;
	}
	return head;
}

void saveToFile(node head){
	f = fopen("data.txt","w+");
	for(node p = head; p != NULL; p = p->next){
		fprintf(f,"\n%s;%02d;%02d;%04d;%.2f;%d;%s;%s;%s",
		p->data.name,p->data.birthDay.day,p->data.birthDay.month,
		p->data.birthDay.year,p->data.height,p->data.shirtNumber,
		p->data.role,p->data.nation,p->data.dominantFoot);
	}
	printf("\n[!] - Luu du lieu vao file thanh cong!\n");
	fclose(f);
	f = fopen("data.txt","r+");
}

node deletePlayer(node head, int shirtNumber){
    int found = 0;
    node p = head;
    while (p != NULL){
        if (p->data.shirtNumber == shirtNumber){
            found = 1;
            head = deleteNode(head, shirtNumber); 
            p = head;
        }
		else
        	p = p->next;
    }
    printf("\n-----------------------------------\n");
    if(found)
        printf("[!] - Xoa cau thu thanh cong!");
    else
        printf("[!] - Khong tim thay cau thu voi so ao %d!", shirtNumber);
    printf("\n-----------------------------------\n");
    system("pause");
    return head;
}

node changePlayerData(FootballPlayer player, int shirtNumber){
	int found = 0;
	node head = insertDataToNode(player);
	for(node p = head; p != NULL; p = p->next){						
		if(p->data.shirtNumber == shirtNumber){
			found = 1;
			printf("\nNhap ten cau thu moi: ");fflush(stdin);
			gets(p->data.name);uppercaseFirtsLetter(p->data.name);
			printf("\nNhap ngay thang nam sinh moi (DD MM YYYY): ");
			scanf("%d %d %d",&p->data.birthDay.day,
			&p->data.birthDay.month,&p->data.birthDay.year);
			printf("\nNhap chieu cao moi: ");
			scanf("%f",&p->data.height);
			printf("\nNhap so ao moi: ");
			scanf("%d",&p->data.shirtNumber);
			printf("\nNhap vi tri moi: ");fflush(stdin);
			gets(p->data.role);uppercaseFirtsLetter(p->data.role);
			printf("\nNhap quoc tich moi: ");fflush(stdin);
			gets(p->data.nation);uppercaseFirtsLetter(p->data.nation);
			printf("\nNhap chan thuan moi: ");fflush(stdin);
			gets(p->data.dominantFoot);uppercaseFirtsLetter(p->data.dominantFoot);
		}
	}
	
	printf("\n-----------------------------------\n");
	(found) ? printf("[!] - Sua thong tin cau thu thanh cong!"): 
			printf("[!] - Khong tim thay cau thu voi so ao %d!", shirtNumber);
	printf("\n-----------------------------------\n");
	system("pause");
	return head;
}

void listPlayer(node head){
	printTitle();
	int STT = 1;
	for(node p = head; p != NULL; p = p->next){
		printPlayer(p,STT);
		STT++;
	}
	printBoardLine();	
}

void swap(node &p, node &q){
	FootballPlayer temp = p->data;
	p->data = q->data;
	q->data = temp;
}

void printPlayersByIncreasingShirtNumber(node head){
	for(node p = head; p != NULL; p = p->next)
		for(node q = p->next; q != NULL; q = q->next)
			if(p->data.shirtNumber > q->data.shirtNumber)
				swap(p, q);
	listPlayer(head);
}

void printPlayerByABCName(node head){
	for(node p = head; p != NULL; p = p->next)
		for(node q = p->next; q != NULL; q = q->next)
			if(stricmp(p->data.name,q->data.name) > 0)
				swap(p, q);
	listPlayer(head);
}

bool checkPlayersName(char playerName[], char findingName[]){
	strlwr(playerName);
	strlwr(findingName);
	if(strstr(playerName,findingName))
		return true; 
	else	
		return false;
}

void findName(node head, char findingName[]){
	printTitle();
	int STT = 1;
	for(node p = head; p != NULL; p = p->next){
		if(checkPlayersName(p->data.name,findingName)){
			uppercaseFirtsLetter(p->data.name);
			printPlayer(p,STT);
			STT++;
		}
	}
	printBoardLine();
}

void findShirtNumber(node head, int findingNumber){
	printTitle();
	int STT = 1;
	for(node p = head; p != NULL; p = p->next){
		if(p->data.shirtNumber == findingNumber){
			printPlayer(p,STT);
			STT++;
		}
	}
	printBoardLine();
}

char *chooseTheRole(int choose){
	char *role = (char*)malloc(sizeof(char) * 30);
	switch(choose){
		case 1:
			strcpy(role,"Thu Mon");
			break;
		case 2:
			strcpy(role,"Hau Ve");
			break;
		case 3:
			strcpy(role,"Tien Ve");
			break;
		case 4:
			strcpy(role,"Tien Dao");
			break;
	}
	return role;
}

char *chooseTheDomninantFoot(int choose){
	char *dominantFoot = (char*)malloc(sizeof(char) * 3);
	switch(choose){
		case 1:
			strcpy(dominantFoot,"R");
			break;
		case 2:
			strcpy(dominantFoot,"L");
			break;
	}
	return dominantFoot;
}

void printPlayerByRole(node head, char role[]){
	printTitle();
	int STT = 1;
	for(node p = head; p != NULL; p = p->next){
		if(stricmp(role,p->data.role) == 0){
			printPlayer(p,STT);
			STT++;
		}
	}
	printBoardLine();
}

void printPlayerByDomninantFoot(node head, char dominantFoot[]){
	printTitle();
	int STT = 1;
	for(node p = head; p != NULL; p = p->next){
		if(stricmp(dominantFoot,p->data.dominantFoot) == 0){
			printPlayer(p,STT);
			STT++;
		}
	}
	printBoardLine();
}

int main()
{
	FootballPlayer player;
	int choose;
	node head = initHead();
	do{
		f = fopen("data.txt","r+");
		printMenu();
		scanf("%d",&choose);
		switch(choose){
			case 0:
				printf("\n--------------------------------\n");
				printf("XIN CHAO VA HEN GAP LAI!");
				break;
			case 1:
				printf("\n[1] - Danh sach cac cau thu.\n");
				head = insertDataToNode(player);
				listPlayer(head);
				system("pause");
				system("cls");
				break;
			case 2:
				printf("\n[2] - Them cau thu moi.\n");
				printf("-----------------------\n");
				head = addNewPlayer(player, head);
				printf("\n[*] - Danh sach cac cau thu sau khi them:\n");
				listPlayer(head);
				fclose(f);
				saveToFile(head);
				system("pause");
				system("cls");
				break;
			case 3:
				printf("\n[3] - Xoa cau thu.\n");
				printf("------------------\n");
				int deleteShirtNumber;
				printf("Nhap so ao cua cau thu muon xoa: ");
				scanf("%d",&deleteShirtNumber);
				head = deletePlayer(head, deleteShirtNumber);
				printf("\n[*] - Danh sach cac cau thu sau khi xoa:\n");
				listPlayer(head);
				fclose(f);
				saveToFile(head);
				system("pause");
				system("cls");
				break;
			case 4:
				printf("\n[4] - Chinh sua thong tin cau thu.\n");
				printf("----------------------------------\n");
				int changeShirtNumber;
				printf("Nhap so ao cua cau thu muon chinh sua: ");
				scanf("%d",&changeShirtNumber);
				head = changePlayerData(player, changeShirtNumber);
				printf("\n[*] - Danh sach cac cau thu sau khi sua:\n");
				listPlayer(head);
				fclose(f);
				saveToFile(head);
				system("pause");
				system("cls");
				break;
			case 5:
				int sortChoose;
				printf("\n[5] - Sap xep.\n");
				printf("--------------\n");
				printf("\t[1] - Sap xep 'So ao' theo thu tu 'Tang dan'.\n");
				printf("\t[2] - Sap xep 'Ten' theo thu tu ABC.\n");
				printf("\tNhap lua chon: ");
				scanf("%d",&sortChoose);
				switch(sortChoose){
					case 1:
						head = insertDataToNode(player);
						printf("\n[1] - Danh sach cac cau thu theo thu tu so ao tang dan.\n");
						printPlayersByIncreasingShirtNumber(head);
						fclose(f);
						system("pause");
						system("cls");
						break;
					case 2:
						head = insertDataToNode(player);
						printf("\n[2] - Danh sach cac cau thu theo thu tu ABC.\n");
						printPlayerByABCName(head);
						fclose(f);
						system("pause");
						system("cls");
						break;
				}
				system("cls");
				break;
			case 6:
				printf("\n[6] - Tim kiem cau thu.\n");
				printf("-----------------------\n");
				int findChoose;
				printf("\t[1] - Tim kiem theo 'Ten'.\n");
				printf("\t[2] - Tim kiem theo 'So ao'.\n");
				printf("\tNhap lua chon: ");
				scanf("%d",&findChoose);
				switch(findChoose){
					case 1:
						printf("\t[1] - Tim kiem theo ten.\n");
						head = insertDataToNode(player);
						char findingName[30];
						printf("\t\tNhap ki tu hoac ten can tim: ");fflush(stdin);
						gets(findingName);
						printf("\n\t\tDanh sach cac cau thu co ki tu '%s'.\n",findingName);
						findName(head, findingName);
						system("pause");
						system("cls");
						break;
					case 2:
						printf("\t[2] - Tim kiem theo so ao.\n");
						head = insertDataToNode(player);
						int findingNumber;
						printf("\t\tNhap so ao can tim: ");
						scanf("%d",&findingNumber);
						findShirtNumber(head, findingNumber);
						system("pause");
						system("cls");
						break;
				}
				system("cls");
				break;
			case 7:
				printf("\n[7] - Bo loc.\n");
				printf("-------------\n");
				head = insertDataToNode(player);
				int filterChoose;
				printf("\t[1] - Loc theo 'Vi tri'.\n");
				printf("\t[2] - Loc theo 'Chan thuan'.\n");
				printf("\tNhap lua chon: ");
				scanf("%d",&filterChoose);
				switch(filterChoose){
					case 1:
						printf("\tBan mua loc theo vi tri nao?\n");
						printf("\t\t[1] - Thu Mon\n");
						printf("\t\t[2] - Hau Ve\n");
						printf("\t\t[3] - Tien Ve\n");
						printf("\t\t[4] - Tien Dao\n");
						int roleChoose;
						printf("\t\tNhap lua chon: ");
						scanf("%d",&roleChoose);
						printf("\n[%d] - Danh sach cac cau thu o vi tri %s: \n",roleChoose,chooseTheRole(roleChoose));
						printPlayerByRole(head, chooseTheRole(roleChoose));
						system("pause");
						system("cls");
						break;
					case 2:
						printf("\tBan mua loc theo chan thuan nao?\n");
						printf("\t\t[1] - Chan phai (R)\n");
						printf("\t\t[2] - Chan trai (L)\n");
						int footChoose;
						printf("\t\tNhap lua chon: ");
						scanf("%d",&footChoose);
						printf("\n[%d] - Danh sach cac cau thu thuan chan (%s): \n",
						footChoose,chooseTheDomninantFoot(footChoose));
						printPlayerByDomninantFoot(head, chooseTheDomninantFoot(footChoose));
						system("pause");
						system("cls");
						break;
				}
				system("cls");
				break;
		}	
	}
	while(choose!=0);
	return 0;
}
