#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

int main(){
	int i, j, k, k2;
	int ty;
	int count = 0;
	int count2;
	int m1=0;
	int m2=0;
	char c1, c2;
	char map[100][30][30];
	char name[100][N];
	char time[100];
	char score[100];
	char name_comp[N];       //입력받는 이름
	char trash[N];
	FILE *ofp;
	FILE *ifp;
	FILE *ofp2;
	FILE *ifp2;
	ofp = fopen("sokoban", "a"); 
	ifp = fopen("sokoban", "r");
	ofp2 = fopen("sokoban2", "a");
	ifp2 = fopen("sokoban2", "r");
	if (ifp == NULL){
		printf("입력 파일을 읽을 수 없습니다.\n");
		return 0;
	}
	printf("이름 : ");
	i=0;
	while (1){														//이름 입력받아 name_comp에 저장
		c1 = getchar();											
		if ((c1 == ' ') || i == N){
			while ((c1=getchar()) != '\n')
			;	
			printf("이름을 다시 입력하세요 : ");
			i=0;
			continue;
		}
		if (c1 == '\n' || c1 == EOF){
			name_comp[i++] = '\0';
			break;
		}
		name_comp[i++] = c1;
	}


	i=0;
	while (1){										//중복된 이름이 나올 때까지 이름, 시간, 맵 읽어오고
		count = 0;									//이름, 시간, 맵 sokoban2에 쓰기
		fscanf(ifp, "%s\n", &name[i]);
		if (feof(ifp) != 0)
			break;
		fscanf(ifp, "%d\n", &time[i]);
		m1=0;
		while(1){
			fgets(map[i][m1], sizeof(map[i][m1]), ifp);
			k = strncmp(map[i][m1], "end", 3);
			if (k==0)
				break;
			m1++;
			count++;
		}

		fprintf(ofp2, "%s\n", name[i]);
		count2 = count;
		k2 = strcmp(name[i], name_comp);
		if (k2 == 0){
			printf("데이터를 불러옵니다.\n");
			printf("이름 : %s, 시간 : %d\n", name[i], time[i]);
			m1 -= count2;
			for(;count2>=0;count2--){
				printf("%s", map[i][m1]);
				m1++;
			}
			//name[i], time[i], map[i] - 현재 플레이어 상태
			//불러온 뒤 게임 플레이
			//게임 종료할 때 배열의 같은 위치에 저장
			fprintf(ofp2, "%d\n", time[i]); //sokoban2에 시간 기록
			ty = i;
			m1--;
			count2 = count;
			m1 -= count;
			for(; count2>=0; count2--){		//sokoban2에 맵 기록
				fputs(map[i][m1], ofp2);
				m1++;
			}
			printf("불러온 플레이어 상태 이후 저장 중\n");
			i++;
			while (1){
				fscanf(ifp, "%s\n", &name[i]);
				if (feof(ifp) != 0)
					break;
				fprintf(ofp2, "%s\n", name[i]);
				fscanf(ifp, "%d\n", &time[i]);
				fprintf(ofp2, "%d\n", time[i]);
				while(1){
					fgets(map[i][m1], sizeof(map[i][m1]), ifp);
					fputs(map[i][m1], ofp2);
					k = strncmp(map[i][m1], "end", 3);
					if (k==0)
						break;
					m1++;
				}
				i++;
			}
			break;
		}
		count2 = count;
		m1 -= count;
		fprintf(ofp2, "%d\n", time[i]); //sokoban2에 시간 기록
		for(; count>=0; count--){		//sokoban2에 맵 기록
			fputs(map[i][m1], ofp2);
			m1++;
		}
		i++;
	}		
	//-------while문 끝--------k==0일 때 sokoban2에 저장 끝------------------
	

	if (k2 != 0){
		//게임 플레이 후 time[i], map[i]에 저장
		fprintf(ofp2, "%s\n", name_comp[i]);
		//fprintf로 time, map 저장
		//
		//return 0; // 저장 후 프로그램 종료
	}
//--------------sokoban2에 저장 끝--------------------
	i=0;
	m1=0;
	while(1){
		fscanf(ifp2, "%s", &name[i]);
		if(feof(ifp2) != 0)
			break;
		fprintf(ofp, "%s\n", name[i]);
		fscanf(ifp2, "%d\n", &time[i]);
		fprintf(ofp, "%d\n", time[i]);
		while(1){
			fgets(map[i][m1], sizeof(map[i][m1]), ifp2);
			fputs(map[i][m1], ofp);
			k = strncmp(map[i][m1], "end", 3);
			if (k==0)
				break;
			m1++;
			count++;
		}
		m1--;
		count--;
		m1 -= count;
			
	}

		
		printf("이름은 : %s\n", name[ty]);
		printf("시간은 : %d\n", time[ty]);
		m1 -= count;
		while(1){
			k = strncmp(map[ty][m1], "end", 3);
			printf("%s", map[ty][m1]);
			if (k==0)
				break;
			m1++;
		}
	fclose(ofp);
	fclose(ifp);
	fclose(ifp2);
	fclose(ofp2);
	char so[N] = "sokoban";
	remove(so);
	char mover[N];	
	ofp = fopen("sokoban", "a"); 
	ifp = fopen("sokoban", "r");
	ofp2 = fopen("sokoban2", "a");
	ifp2 = fopen("sokoban2", "r");
	while (1){
		fgets(mover, 30, ifp2);
		if (feof(ifp2) != 0)
			break;
		fputs(mover, ofp);
		printf("mover : %s\n", mover);
	}
	fclose(ifp);
	fclose(ofp);
	fclose(ifp2);
	fclose(ofp2);
		char so2[N] = "sokoban2";
		remove(so2);
}
