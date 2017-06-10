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
	int stage;
	char c1, c2;
	char map[100][30][30];
	char name[100][N];
	int time[100];
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
		fscanf(ifp, "%s", &name[i]);
		if (feof(ifp) != 0)
			break;
		fscanf(ifp, "%d\n", &time[i]);
		m1=0;
		while(1){
			if(map[i][m1-1][m2-2] == 'd'){
				break;
			}
			m2=0;
			while(map[i][m1][m2-1] != '\n'){
				fscanf(ifp, "%c", &map[i][m1][m2]);
				if (map[i][m1][m2-1] == 'p'){
					stage = map[i][m1][m2] - '0';
				}
				m2++;
			}
			m1++;
		}

		fprintf(ofp2, "%s\n", name[i]);
		k2 = strncmp(name[i], name_comp, sizeof(name_comp));
		if (k2 == 0){
			printf("데이터를 불러옵니다.\n");
			printf("이름 : %s, 시간 : %d\n", name[i], time[i]);
			printf("stage %d\n", stage);
			m1=0;
			while(1){
				if(map[i][m1-1][m2-2] == 'd'){
					break;
				}
				m2=0;
				while(map[i][m1][m2-1] != '\n'){
					printf("%c", map[i][m1][m2]);
					m2++;
				}
				m1++;
			}

			//name[i], time[i], map[i] - 현재 플레이어 상태
			//불러온 뒤 게임 플레이
			//
			//
			//게임 종료할 때 배열의 같은 위치에 저장
			fprintf(ofp2, "%d\n", time[i]); //sokoban2에 시간 기록
			ty = i;
			m1=0;
			while(map[i][m1-1][m2-2] != 'd'){
				m2=0;
				while(map[i][m1][m2-1] != '\n'){
					fprintf(ofp2, "%c", map[i][m1][m2]);

					m2++;
				}
				m1++;
			}
	
			while (1){
				fgets(name[i], sizeof(name[i]), ifp);
				if (feof(ifp) != 0)
					break;
				fputs(name[i], ofp2);
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
			i++;		
			break;
		}
		fprintf(ofp2, "%d\n", time[i]);
		m1=0;
		while(1){
			m2=0;
			while(1){
				fprintf(ofp2, "%c", map[i][m1][m2]);
				if(map[i][m1][m2] == '\n'){
					break;
				}
				m2++;
			}
			if(map[i][m1][m2-1] == 'd'){
				break;
			}
			m1++;
		}
		i++;
	}
	//-------while문 끝--------k2==0일 때 sokoban2에 저장 끝------------------
	
	if (k2 != 0){
		//게임 플레이 후 time[i], map[i]에 저장
		fprintf(ofp2, "%s\n", name_comp);
		//fprintf로 sokoban2에 time, map 저장
		//
	}
//--------------k2!=0일 때 sokoban2에 저장 끝--------------------
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
	}
	fclose(ifp);
	fclose(ofp);
	fclose(ifp2);
	fclose(ofp2);
		char so2[N] = "sokoban2";
		remove(so2);
}
