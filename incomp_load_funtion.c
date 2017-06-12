/*구현 안 된 부분 - 세이브파일 로드
 * 게임 실행시 loader로 불러오고 sokoban 대신midSave에 중간저장
 * 종료할 때 mover함수로 sokoban-> sokoban2로 옮김
 * 같은 이름이 나오면 midSave->sokoban2로 옮긴 후 다시 sokoban->sokoban2 재개
 * 이후 모두 옮겨지면 sokoban 파일을 삭제하고 sokoban2를 sokoban으로 옮김
 * sokoban2를 삭제
 *
 *
 *
#include<string.h>
int saveCheck;
void loader(char name_comp[10]){
   int i, j, k, k2;
   int ty;
   int count = 0;
   int count2;
   int m1=0;
   int m2=0;
   int stage;
   char c1, c2;
   char map[100][30][30];
   float time[100];
   char trash[N];
   char name[100][N];
   FILE *ofp;
   FILE *ifp;
   FILE *ofp2;
   FILE *ifp2;
   ofp = fopen("sokoban", "a");
   ifp = fopen("sokoban", "r");
   ofp2 = fopen("sokoban2", "a");
   ifp2 = fopen("sokoban2", "r");


   i=0;
   while (1){                             //중복된 이름이 나올 때까지 이름, 시간, 맵 읽어오기
      count = 0;
      fscanf(ifp, "%s", &name[i]);
      printf("%s", name[i]);
      if (feof(ifp) != 0)
         break;
      fscanf(ifp, "%f", &time[i]);		
      fscanf(ifp, "%s", &trash);			//sec 부분 지우기
      m1=0;
      m2=0;
      while(1){
         if(map[i][m1-1][m2-2] == 'd'){
            break;
         }
         m2=0;
         while(map[i][m1][m2-1] != '\n'){
            fscanf(ifp, "%c", &map[i][m1][m2]);
            if (map[i][m1][m2-1] == 'p'){
               stage = map[i][m1][m2] - '0';  //char형 배열로 받아온 map에서 스테이지 int로 바꿈
            }
            m2++;
         }
         m1++;
      }

      k2 = strncmp(name[i], name_comp, strlen(name_comp));
      if (k2 == 0){
         printf("데이터를 불러옵니다.\n");
         printf("이름 : %s, 시간 : %.2f\n", name[i], time[i]); // name은 start_game 배열에서 받고
         printf("stage %d", stage);                      // time time[i]를 받아오면 됨.
         m1=0;
        while(1){
            if(map[i][m1-1][m2-2] == 'd'){
               break;
            }
            m2=0;
            while(map[i][m1][m2-1] != '\n'){
               mp[stage][m1][m2] = map[i][m1][m2];
               s=stage;
               m2++;
            }
            m1++;
         }
      saveCheck = 1;        //save파일이 있다는 의미=> game 실행할 때 scan_map함수를 불러오지 않음.
      }
      i++;
   }
   if (k2!=0){
      saveCheck = 0;			//save파일이 없음=>game 실행할 때 scan_map 함수를 불러옴.
   }
   fclose(ofp);
   fclose(ifp);
   fclose(ofp2);
   fclose(ifp2);
}


void move(char name_comp[20]){  //게임 종료할 때 sokoban->sokoban2, midSave->sokoban2,
											//마지막으로 sokoban2->sokoban으로 이동시키는 함수

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
   char mover[20];
   int time[100];
   char trash[N];
   FILE *ofp;
   FILE *ifp;
   FILE *ofp2;
   FILE *ifp2;
   ofp = fopen("sokoban", "a");
   ifp = fopen("sokoban", "r");
   ofp2 = fopen("sokoban2", "a");
   ifp2 = fopen("sokoban2", "r");

   while (1){                             //중복된 이름이 나올 때까지 이름, 시간, 맵 읽어오고
     count = 0;                          //이름, 시간, 맵 sokoban2에 쓰기
     fgets(name[i], sizeof(name[i]), ifp);
     if (feof(ifp) != 0)
        break;
     fscanf(ifp, "%d", &time[i]);
     fscanf(ifp, "%s", &trash);
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
    k2 = strncmp(name[i], name_comp, strlen(name_comp));
    if (k2 == 0){				//같은 이름이 존재하면 midSave에서 데이터를 덮어씌옴.
       FILE *mifp;
       mifp = fopen("midSave", "r");
       fgets(name[i], sizeof(name[i]), mifp);
       fputs(name[i], ofp2);
       fscanf(mifp, "%d", &time[i]);
       fprintf(ofp2, "%dsec\n", time[i]);
       fscanf(mifp, "%s", &trash);
       m1=0;
       while(1){
          fgets(map[i][m1], sizeof(map[i][m1]), mifp);
          fputs(map[i][m1], ofp2);
          k = strncmp(map[i][m1], "end", 3);
          if (k==0){
             break;
          }
          m1++;
       }
        while (1){
           fgets(name[i], sizeof(name[i]), ifp);
           if (feof(ifp) != 0)
              break;
           fputs(name[i], ofp2);
           fscanf(ifp, "%d\n", &time[i]);
           fprintf(ofp2, "%dsec\n", time[i]);
           fscanf(ifp, "%s", &trash);
           while(1){
              fgets(map[i][m1], sizeof(map[i][m1]), ifp);
              fputs(map[i][m1], ofp2);
              k = strncmp(map[i][m1], "end", 3);
              if (k==0){
                 break;
              }
              m1++;
           }
           i++;
        }
        i++;
        break;
     }
     fputs(name[i], ofp2);
     fprintf(ofp2, "%dsec\n", time[i]);
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
   //----------------sokoban에 저장된 이름이 있을 경우 sokoban->sokoban2 완료---------
   if(saveCheck == 0){
       FILE *mifp;
       mifp = fopen("midSave", "r");
       fgets(mover, sizeof(mover), mifp); //이름 옮김
       fputs(mover, ofp2);
       fgets(mover, sizeof(mover), mifp); //시간 옮김
       fputs(mover, ofp2);
       m1=0;
       while(1){
          fgets(map[i][m1], sizeof(map[i][m1]), mifp);
          fputs(map[i][m1], ofp2);
          k = strncmp(map[i][m1], "end", 3);
          if (k==0)
             break;
          m1++;
       }
   }
       //------------sokoban에 저장된 이름이 없을 경우 skoban->sokoban2 완료--------

   fclose(ofp);
   fclose(ifp);
   fclose(ifp2);
   fclose(ofp2);
   char so[N] = "sokoban";
   remove(so); 								  //sokoban 삭제
   ofp = fopen("sokoban", "a");
   ifp = fopen("sokoban", "r");
   ofp2 = fopen("sokoban2", "a");
   ifp2 = fopen("sokoban2", "r");
   while (1){ 										//sokoban2 -> sokoban으로 옮김
      fgets(mover, sizeof(mover), ifp2);
      fputs(mover, ofp);
      if (feof(ifp2) != 0)
         break;
   }
   fclose(ifp);
   fclose(ofp);
   fclose(ifp2);
   fclose(ofp2);
      char so2[N] = "sokoban2";
      remove(so2); 									//sokoban2 삭제
}
*/
