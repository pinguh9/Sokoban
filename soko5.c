#include<stdio.h>
#include<time.h>//score기록을 위해서 사용함
#include<stdlib.h>
#include<termio.h>
#define K 5
#define N 14
#define M 30
//undo 전역변수 목록
int ud_max = 5;
int ud_mp[5][N][M];
int ud_count = 0; //플레이어 움직일때마다 1씩늘어남. undo사용시 1씩 줄어들고 ud_max이상으로 커지지않음.
char mp[K][N][M],c,name[10];//mp배열을 map파일로 부터 내용을 읽어서 저장시키기 위한 배열임 name배열은 이름을 받기 위한 배열임
char ospot[K][N][M]; //상자 위치를 저장하기 위해서 새로운 배열을 저장시킴 ud는 undo에서 내용을 저장시키기 위해서 사용한 배열임
int i,j,k,s,x,check_box,b,q,box,place,box_place[5];//i,j,k는 배열의 저장을 위해서 사용한 변수이고 x는 getch()함수의 입력값을 받기 위해서 사용 되었음
//box와 place는 파일에서 오류를 점검할 때에 사용하기 위해서 선언했음
clock_t start,save,end,stage[5];//start는 main함수에서 돌기 시작할 때에 시간으로 생각했고,save는 저장할 때에 시간,end는 stage가 끝났을 때의 시간으로 선언해주었음

//ud_mp에 현재 맵 복사
void undo_init(int stage){
	int w,x,y;
	for(y=0;y<N;y++)
		for(x=0;x<M;x++)
			for(w=0;w<ud_max;w++)
				ud_mp[w][y][x] = mp[stage][y][x];
        //undo 가능 수를 0으로 초기화
	ud_count = 0;
}//맵바뀔떄마다 호출

//log를 한 칸 씩 오른쪽으로 옮김, 현재 맵 상황을 log에 추가
void undo_logging(){
	int w, x, y;

  //4<-3, 3<-2, 2<-1, 1<-0 으로 맵을 복사해서 이동시킴.
	for(w = ud_max-2; w>=0; w--){
		for(y=0;y<N; y++)
			for(x=0;x<M;x++)
				ud_mp[w+1][y][x] = ud_mp[w][y][x];
	}

  //0번째에 현재 맵을 복사
	for(w=0;w<ud_max-1;w++)
	{
		for(y=0;y<N;y++)
			for(x=0;x<M;x++)
				ud_mp[0][y][x] = mp[s][y][x];
	}

  //ud_count는 최대값을 넘지않음.
	if(ud_count<ud_max)
		ud_count++;
}

//맵에 log를 반영하고, log를 한칸씩 왼쪽으로 옮김.
void undo_delogging(){
	int w,x,y;

	if(ud_count>0)
	{
		for(y=0;y<N;y++)
			for(x=0;x<M;x++)
				mp[s][y][x] = ud_mp[0][y][x];

		for(w=0;w<ud_max-1;w++){
			for(y=0;y<N;y++)
				for(x=0;x<M;x++)
					ud_mp[w][y][x] = ud_mp[w+1][y][x];

		}

		for(y=0;y<N;y++)
			for(x=0;x<M;x++)
				ud_mp[ud_max-1][y][x] = 0;
		ud_count--;

		}
	}

void scan_map(){
  FILE *re;
  re=fopen("map.txt","r");//map파일을 읽기 전용으로 열어줌
  for(i=0;i<5;i++){
  for(j=0;j<N;j++){
  for(k=0;k<M;k++){
    fscanf(re,"%c",&mp[i][j][k]);//for으로 반복해서 배열을 저장시킴
    if(mp[i][j][k]=='\n')//배열이 띄어쓰기가 되어진 상황이기 때문에 j를 증가시켜서 배열의 2차원 부분을 늘려줌
      break;
    else if(mp[i][j][k]=='O'){
    ospot[i][j][k]='O';
    box_place[i]++;
  }
}
  if(mp[i][j][k]=='m')
  break;
  }
  if(mp[i][j][k]=='d')
  break;
  }
}
void error_map(int stage){
  for(i=stage;i<stage+1;i++)
  for(j=0;j<N;j++)
  for(k=0;k<M;k++){
    if(mp[i][j][k]=='$')// 반복문을 써서 박스가 있는 위치에서는 box라는 박스의 수를 저장시키는 변수를 증가시켜서 박스의 수를 저장시킴
    box++;
    else if(mp[i][j][k]=='O')//반복문을 써서 상자 위치에 있는 경우에는 place라는 상자 위치의 수를 저장시키는 변수를 증가시켜서 장소의 수를 저장시킴
    place++;
  }
  if(box!=place){
    printf("맵 파일이 올바르지 않습니다");//만약 상자의 수와 장소의 수가 같지 않으면 맵파일이 올바르지 않다는 오류를 출력시키고 프로그램을 종료시킴
  exit(1);
}
}

int getch(){// 문자를 입력받는 함수로 입력받은 문자를 출력하지 않는 형태로 실습 때에 사용하였던 함수를 그대로 인용하였음
int ch;
struct termios buf;
struct termios save;

tcgetattr(0,&save);
buf=save;

buf.c_lflag&=~(ICANON|ECHO);
buf.c_cc[VMIN]=1;
buf.c_cc[VTIME]=0;

tcsetattr(0,TCSAFLUSH,&buf);
ch=getchar();
tcsetattr(0,TCSAFLUSH,&save);

return ch;
}
void print_map(int stage){//맵을 출력시키는 함수
  printf("   Hello ");
  for(i=0;i<M;i++){
  printf("%c",name[i]);//입력받은 이름을 출력시키기 위해서 반복문을 사용함
  if(name[i]=='\n')
  break;
}
  printf("\n");
for(i=stage;i<stage+1;i++){
for(j=1;j<N;j++){
for(k=0;k<M;k++){
  printf("%c",mp[i][j][k]);//맵을 화면에 출력시키기 위해서 반복문을 사용함
  if(mp[i][j][k]=='\n')
    break;
}
if(mp[i][j][k]=='m')
break;
}
if(mp[i][j][k]=='d')
break;
}
printf("\n");
printf("(command)");
}
void save_map(int stage,double timer){//맵을 배열에 저장하는 함수
  FILE *sk;
  sk=fopen("sokoban","w");//소코반 파일을 덮어쓰기 위해서 열음
  for(i=0;i<M;i++){
	  fprintf(sk,"%c",name[i]);//이름을 소코반 파일에 저장시킴
	  if(name[i]=='\n')//enter값을 받으면 반복문을 탈출하고 이름저장을 멈춤
		  break;
  }
	fprintf(sk,"%.2fsec\n",(double)(timer-start)/CLOCKS_PER_SEC);//저장되어있는 점수를 기록함
	fprintf(sk,"map%d",s+1);//몇 번째 맵인지를 파일에 저장시킴
	fprintf(sk,"\n");
	for(i=stage;i<stage+1;i++){
		for(j=1;j<N;j++){
			for(k=0;k<M;k++){
				fprintf(sk,"%c",mp[i][j][k]);//저장된 배열의 내용을 sokoban파일에 저장시킴
				if(mp[i][j][k]=='\n')
					break;
			}
			if(mp[i][j][k]=='m')
				break;
		}
		if(mp[i][j][k]=='d')
			break;
	}
	fprintf(sk,"\nend");
  fclose(sk);
}
void move_map(char x){
if(x=='h'){
  for(j=0;j<N;j++)
  for(k=0;k<M;k++)
  if(mp[s][j][k]=='@'){ //캐릭터의 위치를 찾기 위해서 조건을 걸음
  if(mp[s][j][k-1]==' '&&ospot[s][j][k]!='O'){//캐릭터 왼쪽이 여백이고 캐릭터의 현재 위치가 박스저장소가 아니면 여백으로 캐릭터를 밀음
  mp[s][j][k]=' ';
  mp[s][j][k-1]='@';
  }
  else if(mp[s][j][k-1]=='$'&&mp[s][j][k-2]=='$'){//캐릭터 왼쪽에 박스가 있고 그 왼쪽에 또 박스가 있으면 박스가 밀리지 않음
  mp[s][j][k]='@';
  mp[s][j][k-1]='$';
  mp[s][j][k-2]='$';
}
  else if(ospot[s][j][k]!='O'&&mp[s][j][k-1]=='$'&&(mp[s][j][k-2]==' '||mp[s][j][k-2]=='O')){
    //캐릭터 왼쪽에 박스가 있고 그 왼쪽이 벽이 아니라면 캐릭터와 박스가 왼쪽으로 밀림
  mp[s][j][k]=' ';
  mp[s][j][k-1]='@';
  mp[s][j][k-2]='$';
  }
  else if(ospot[s][j][k]=='O'&&mp[s][j][k-1]=='$'&&mp[s][j][k-2]=='O'){
    //현재 캐릭터 위치가 박스 저장소고 그 왼쪽이 박스고 박스의 왼쪽이 박스 저장소라면
    mp[s][j][k]='O';//원래 위치에 박스
    mp[s][j][k-1]='@';//캐릭터 이동
    mp[s][j][k-2]='$';//박스 이동
  }
  else if(ospot[s][j][k]=='O'&&(mp[s][j][k-1]==' '||mp[s][j][k-1]=='O')){//지금 캐릭터의 위치가 박스를 넣어야 되는 위치이고 움직이는 곳이 여백이나
    //다른 박스를 넣어야 되는 위치면 움직이게 함
  mp[s][j][k]='O';
  mp[s][j][k-1]='@';
}
else if(ospot[s][j][k]=='O'&&mp[s][j][k-1]==' '){
  //박스 위치를 저장한 배열의 위치가 현재 캐릭터의 위치이고 그 왼쪽이 공백이면 캐릭터를 왼쪽으로 밀고 상자 위치도 출력해줌
 mp[s][j][k]='O';
 mp[s][j][k-1]='@';
 }
 else if(mp[s][j][k-1]=='O'){//캐릭터 위치 옆이 박스 저장소면
   mp[s][j][k]=' ';
   mp[s][j][k-1]='@';//캐릭터 이동
 }
 system("clear");
 print_map(s);
  }
    }
else if(x=='k'){//앞에서 움직이는 거랑 방향만 다르기 때문에 코드의 알고리즘 형태는 똑같음
  for(j=0;j<N;j++)
    for(k=0;k<M;k++)
    if(mp[s][j][k]=='@'){
    if(mp[s][j-1][k]==' '&&ospot[s][j][k]!='O'){
    mp[s][j][k]=' ';
    mp[s][j-1][k]='@';
    }
    else if(mp[s][j-1][k]=='$'&&mp[s][j-2][k]=='$'){
    mp[s][j][k]='@';
    mp[s][j-1][k]='$';
    mp[s][j-2][k]='$';
    }
    else if(ospot[s][j][k]!='O'&&mp[s][j-1][k]=='$'&&(mp[s][j-2][k]==' '||mp[s][j-2][k]=='O')){
    mp[s][j][k]=' ';
    mp[s][j-1][k]='@';
    mp[s][j-2][k]='$';
    }
    else if(ospot[s][j][k]=='O'&&mp[s][j-1][k]=='$'&&mp[s][j-2][k]=='O'){
      mp[s][j][k]='O';
      mp[s][j-1][k]='@';
      mp[s][j-2][k]='$';
    }
    else if(ospot[s][j][k]=='O'&&(mp[s][j-1][k]==' '||mp[s][j-1][k]=='O')){
    mp[s][j][k]='O';
    mp[s][j-1][k]='@';
    }
    else if(ospot[s][j][k]=='O'&&mp[s][j-1][k]==' '){
     mp[s][j][k]='O';
     mp[s][j-1][k]='@';
     }
     else if(mp[s][j-1][k]=='O'){
       mp[s][j][k]=' ';
       mp[s][j-1][k]='@';
     }
    system("clear");
    print_map(s);
    }
  }

else if(x=='l'){//마찬가지로 똑같음
  for(j=0;j<N;j++)
  for(k=0;k<M;k++)
  if(mp[s][j][k]=='@'){
  if(mp[s][j][k+1]==' '&&ospot[s][j][k]!='O'){
  mp[s][j][k]=' ';
  mp[s][j][k+1]='@';
  }
  else if(ospot[s][j][k]!='O'&&mp[s][j][k+1]=='$'&&(mp[s][j][k+2]==' '||mp[s][j][k+2]=='O')){
  mp[s][j][k]=' ';
  mp[s][j][k+1]='@';
  mp[s][j][k+2]='$';
  }
  else if(mp[s][j][k+1]=='$'&&mp[s][j][k+2]=='$'){
  mp[s][j][k]='@';
  mp[s][j][k+1]='$';
  mp[s][j][k+2]='$';
  }
  else if(ospot[s][j][k]=='O'&&mp[s][j][k+1]=='$'&&mp[s][j][k+2]=='O'){
    mp[s][j][k]='O';
    mp[s][j][k+1]='@';
    mp[s][j][k+2]='$';
  }
  else if(ospot[s][j][k]=='O'&&(mp[s][j][k+1]==' '||mp[s][j][k+1]=='O')){
  mp[s][j][k]='O';
  mp[s][j][k+1]='@';
  }
  else if(ospot[s][j][k]=='O'&&mp[s][j][k+1]==' '){
   mp[s][j][k]='O';
   mp[s][j][k+1]='@';
   }
   else if(mp[s][j][k+1]=='O'){
     mp[s][j][k]=' ';
     mp[s][j][k+1]='@';
   }
  system("clear");
  print_map(s);
  }
}
else if(x=='j'){//마찬가지임
  for(j=0;j<N;j++)
    for(k=0;k<M;k++)
    if(mp[s][j][k]=='@'){
    if(mp[s][j+1][k]==' '&&ospot[s][j][k]!='O'){
    mp[s][j][k]=' ';
    mp[s][j+1][k]='@';
    }
    else if(mp[s][j+1][k]=='$'&&mp[s][j+2][k]=='$'){
    mp[s][j][k]='@';
    mp[s][j+1][k]='$';
    mp[s][j+2][k]='$';
    }
    else if(ospot[s][j][k]!='O'&&mp[s][j+1][k]=='$'&&(mp[s][j+2][k]==' '||mp[s][j+2][k]=='O')){
    mp[s][j][k]=' ';
    mp[s][j+1][k]='@';
    mp[s][j+2][k]='$';
    }
    else if(ospot[s][j][k]=='O'&&mp[s][j+1][k]=='$'&&mp[s][j+2][k]=='O'){
      mp[s][j][k]='O';
      mp[s][j+1][k]='@';
      mp[s][j+2][k]='$';
    }
    else if(ospot[s][j][k]=='O'&&(mp[s][j+1][k]==' '||mp[s][j+1][k]=='O')){
    mp[s][j][k]='O';
    mp[s][j+1][k]='@';
  }
  else if(ospot[s][j][k]=='O'&&mp[s][j+1][k]==' '){
   mp[s][j][k]='O';
   mp[s][j+1][k]='@';
   }
   else if(mp[s][j+1][k]=='O'){
     mp[s][j][k]=' ';
     mp[s][j+1][k]='@';
   }
  system("clear");
  print_map(s);
    }
}
}
void jump_stage(){//stage를 넘기기 위해 만들어낸 함수
  check_box=0;//생각한 방법은 현재 파일을 읽어서 '$'인 부분이 박스 위치를 저장하는 배열의 경우에는 'O'일때 마다 a라는 숫자를 증가시켜서
  //check_box가 box_placep[s]와 똑같은 크기가 되면 모무 다 똑같게 된 상황으로 생각하고,그렇게 되면 다음 스테이지로 넘어가게 하는 방식
for(j=1;j<N;j++)
   for(k=0;k<M;k++){
     if(mp[s][j][k]=='$'&&ospot[s][j][k]=='O')//둘이 같을 때에 a를 증가시켜서
       check_box++;
   }
     for(i=0;i<5;i++){
       if(s==i&&check_box==box_place[i]){//각 블럭의 수이 다 들어갔을 때의 경우에
          s++;//스테이지를 높여주고

          system("clear");
          error_map(s);//맵의 오류가 없는지 확인하고
          print_map(s);//맵을 출력한 뒤
          start=clock();//시간을 초기화 함
          undo_init(s);
          }
     }
if(s==5){//다 깬 거기 때문에
  system("clear");
  printf("\n\n\n\n\n  C O N G R A T U A T E F O R C L E A R ! ! ! !\n\n\n\n\n\n");//축하메시지를 출력하고
  exit(1);//프로그램을 종료함
}
}
void exit_game(){
  system("clear");
  printf("\n\n S E E  Y O U  ");
  for(i=0;i<M;i++){//이름을 화면에 출력시켜줌
  printf("%c ",name[i]);
  if(name[i+1]=='\n'){
    printf(".....");
  break;
}
}
  printf("\n\n\n(Command) %c",x);
   exit(1);//그러고는 프로그램을 종료함
}
void start_game(){
  system("clear");
  printf("Start.....\n");//시작한다는 것을 출력함
  printf("Input name: ");//이름을 입력하라고 출력시킴
  for(i=0;i<10;i++){
  scanf("%c",&name[i]);//이름은 엔터값을 포함해서 최대 10글자 까지 받게 설정되어있음
  if(name[i]=='\n')
  break;
  }
  system("clear");
    scan_map();//맵 파일에서 맵을 읽어 저장한 뒤
    error_map(s);//맵 파일에 오류가 있는지 확인하고
    print_map(s);//오류가 없다면 맵을 출력시킴
}
void display_manual(char x){
  system("clear");
  printf("   Hello ");
  for(i=0;i<M;i++){
  printf("%c",name[i]);
  if(name[i]=='\n')
  break;
}
  printf("\n\n");
  printf("h(왼쪽),j(아래),k(위),l(오른쪽)\n");
  printf("u(undo)\nr(replay)\nn(new)\ne(exit)\ns(save)\nf(fileload)\n");
  printf("d(display help)\nt(top)\n\n\n(Command)%c",x);
}
void replay_game(int s){
  //stage를 나타내는 s값은 초기화 시키지 않은 다음에 맵파일에서 맵을 다시 읽어서 현재 stage에 해당하는 맵을 다시 출력하고 거기서 부터 시작하게함
  system("clear");//화면에서 앞에서 출력된 내용을 싹 다 지워버리고
  scan_map();//다시 맵 파일에서 맵을 읽어서
  print_map(s);//stage에 맞는 맵을 출력시켜줌
}
void new_game(){
  //그리고 맵을 다시 읽어서 1번째 맵부터 다시 출력되도록 함
  system("clear");//앞에서 출력된 내용을 싹 다 지워버리고
	scan_map();//다시 맵파일에서 맵을 받고
  s=0;//스테이지를 초기화하고
  start=clock();
  print_map(s);//맵을 출력함
}
int main(){
 FILE *sk;
 sk=fopen("sokoban","w");//소코반 파일을 덮어쓰기 위해서 열음
 start_game();
  start=clock();
  undo_init(s);

while(1){
  jump_stage();
x=getch();
if(x=='d'){//sokoban게임의 조작법을 알려줌
  display_manual(x);
}
else if(x=='s'){//필요한 내용을 저장함
  save=clock();
  save_map(s,save);
  system("clear");
  print_map(s);
  printf("%c",x);//s를 한 번 더 출력시켜줌
}
else if(x=='e'){//게임을 종료시키는 버튼임
  end=clock();
  save_map(s,end);
  exit_game();
}
else if(x=='h'||x=='j'||x=='k'||x=='l'){//캐릭터를 움직이는 버튼임
  undo_logging();
  move_map(x);
  jump_stage(s);
}
else if(x=='n'){//새로운 게임으로 시작하게 하는 버튼임
 new_game();
 printf("%c",x);
}
else if(x=='u'){// 움직이기 전 상태로 돌아가는 버튼임
 undo_delogging();
 system("clear");
 print_map(s);
 printf("%c",x);
}
else if(x=='r'){//현재 스테이지부터 다시 시작하게 하는 버튼임
  replay_game(s);
	printf("%c",x);
}
}
}
