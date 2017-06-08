#include<stdio.h>
#include<time.h>//score����� ���ؼ� �����
#include<stdlib.h>
#include<termio.h>
#define K 5
#define N 14
#define M 30
int ud_max = 5;
int ud_mp[5][N][M];
int ud_count = 0;
char mp[K][N][M],c,name[10];//mp�迭�� map���Ϸ� ���� ������ �о �����Ű�� ���� �迭�� name�迭�� �̸��� �ޱ� ���� �迭��
char ospot[K][N][M]; //���� ��ġ�� �����ϱ� ���ؼ� ���ο� �迭�� �����Ŵ ud�� undo���� ������ �����Ű�� ���ؼ� ����� �迭��
int i,j,k,s,x,check_box,b,q,box,place,box_place[5];//i,j,k�� �迭�� ������ ���ؼ� ����� �����̰� x�� getch()�Լ��� �Է°��� �ޱ� ���ؼ� ��� �Ǿ���
//box�� place�� ���Ͽ��� ������ ������ ���� ����ϱ� ���ؼ� ��������
clock_t start,save,end,stage[5];//start�� main�Լ����� ���� ������ ���� �ð����� �����߰�,save�� ������ ���� �ð�,end�� stage�� ������ ���� �ð����� �������־���

void undo_init(int stage){
	int w,x,y;
	for(y=0;y<N;y++)
		for(x=0;x<M;x++)
			for(w=0;w<ud_max;w++)
				ud_mp[w][y][x] = mp[stage][y][x];
	ud_count = 0;
}

void undo_logging(){
	int w, x, y;

	for(w = ud_max-2; w>=0; w--){
		for(y=0;y<N; y++)
			for(x=0;x<M;x++)
				ud_mp[w+1][y][x] = ud_mp[w][y][x];
	}

	for(w=0;w<ud_max-1;w++)
	{
		for(y=0;y<N;y++)
			for(x=0;x<M;x++)
				ud_mp[0][y][x] = mp[s][y][x];
	}

	if(ud_count<ud_max)
		ud_count++;
}

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
  re=fopen("map.txt","r");//map������ �б� �������� ������
  //�б� ���ϰ� �ϱ� ���ؼ� map.txt������ �ణ ������ �ؼ� �ٸ� ����� ���� map.txt���Ϸ� �ϸ� �ణ�� ������ ���� ���� ����
  for(i=0;i<5;i++){
  for(j=0;j<N;j++){
  for(k=0;k<M;k++){
    fscanf(re,"%c",&mp[i][j][k]);//for���� �ݺ��ؼ� �迭�� �����Ŵ
    if(mp[i][j][k]=='\n')//�迭�� ���Ⱑ �Ǿ��� ��Ȳ�̱� ������ j�� �������Ѽ� �迭�� 2���� �κ��� �÷���
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
    if(mp[i][j][k]=='$')// �ݺ����� �Ἥ �ڽ��� �ִ� ��ġ������ box��� �ڽ��� ���� �����Ű�� ������ �������Ѽ� �ڽ��� ���� �����Ŵ
    box++;
    else if(mp[i][j][k]=='O')//�ݺ����� �Ἥ ���� ��ġ�� �ִ� ��쿡�� place��� ���� ��ġ�� ���� �����Ű�� ������ �������Ѽ� ����� ���� �����Ŵ
    place++;
  }
  if(box!=place){
    printf("�� ������ �ùٸ��� �ʽ��ϴ�");//���� ������ ���� ����� ���� ���� ������ �������� �ùٸ��� �ʴٴ� ������ ��½�Ű�� ���α׷��� �����Ŵ
  exit(1);
}
}

int getch(){// ���ڸ� �Է¹޴� �Լ��� �Է¹��� ���ڸ� ������� �ʴ� ���·� �ǽ� ���� ����Ͽ��� �Լ��� �״�� �ο��Ͽ���
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
void print_map(int stage){//���� ��½�Ű�� �Լ�
  printf("   Hello ");
  for(i=0;i<M;i++){
  printf("%c",name[i]);//�Է¹��� �̸��� ��½�Ű�� ���ؼ� �ݺ����� �����
  if(name[i]=='\n')
  break;
}
  printf("\n");
for(i=stage;i<stage+1;i++){
for(j=1;j<N;j++){
for(k=0;k<M;k++){
  printf("%c",mp[i][j][k]);//���� ȭ�鿡 ��½�Ű�� ���ؼ� �ݺ����� �����
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
void save_map(int stage,double timer){//���� �迭�� �����ϴ� �Լ�
  FILE *sk;
  sk=fopen("sokoban","w");//���ڹ� ������ ����� ���ؼ� ����
  fprintf(sk,"map%d",s+1);//�� ��° �������� ���Ͽ� �����Ŵ
  fprintf(sk,"\n%.2fsec\n",(double)(timer-start)/CLOCKS_PER_SEC);//����Ǿ��ִ� ������ �����
  for(i=0;i<M;i++){
  fprintf(sk,"%c",name[i]);//�̸��� ���ڹ� ���Ͽ� �����Ŵ
  if(name[i]=='\n')//enter���� ������ �ݺ����� Ż���ϰ� �̸������� ����
  break;
  }
  for(i=stage;i<stage+1;i++){
  for(j=1;j<N;j++){
  for(k=0;k<M;k++){
    fprintf(sk,"%c",mp[i][j][k]);//����� �迭�� ������ sokoban���Ͽ� �����Ŵ
    if(mp[i][j][k]=='\n')
      break;
  }
  if(mp[i][j][k]=='m')
  break;
  }
  if(mp[i][j][k]=='d')
  break;
  }
  fclose(sk);
}
void move_map(char x){
if(x=='h'){
  for(j=0;j<N;j++)
  for(k=0;k<M;k++)
  if(mp[s][j][k]=='@'){ //ĳ������ ��ġ�� ã�� ���ؼ� ������ ����
  if(mp[s][j][k-1]==' '&&ospot[s][j][k]!='O'){//ĳ���� ������ �����̰� ĳ������ ���� ��ġ�� �ڽ�����Ұ� �ƴϸ� �������� ĳ���͸� ����
  mp[s][j][k]=' ';
  mp[s][j][k-1]='@';
  }
  else if(mp[s][j][k-1]=='$'&&mp[s][j][k-2]=='$'){//ĳ���� ���ʿ� �ڽ��� �ְ� �� ���ʿ� �� �ڽ��� ������ �ڽ��� �и��� ����
  mp[s][j][k]='@';
  mp[s][j][k-1]='$';
  mp[s][j][k-2]='$';
}
  else if(ospot[s][j][k]!='O'&&mp[s][j][k-1]=='$'&&(mp[s][j][k-2]==' '||mp[s][j][k-2]=='O')){
    //ĳ���� ���ʿ� �ڽ��� �ְ� �� ������ ���� �ƴ϶�� ĳ���Ϳ� �ڽ��� �������� �и�
  mp[s][j][k]=' ';
  mp[s][j][k-1]='@';
  mp[s][j][k-2]='$';
  }
  else if(ospot[s][j][k]=='O'&&mp[s][j][k-1]=='$'&&mp[s][j][k-2]=='O'){
    //���� ĳ���� ��ġ�� �ڽ� ����Ұ� �� ������ �ڽ��� �ڽ��� ������ �ڽ� ����Ҷ��
    mp[s][j][k]='O';//���� ��ġ�� �ڽ�
    mp[s][j][k-1]='@';//ĳ���� �̵�
    mp[s][j][k-2]='$';//�ڽ� �̵�
  }
  else if(ospot[s][j][k]=='O'&&(mp[s][j][k-1]==' '||mp[s][j][k-1]=='O')){//���� ĳ������ ��ġ�� �ڽ��� �־�� �Ǵ� ��ġ�̰� �����̴� ���� �����̳�
    //�ٸ� �ڽ��� �־�� �Ǵ� ��ġ�� �����̰� ��
  mp[s][j][k]='O';
  mp[s][j][k-1]='@';
}
else if(ospot[s][j][k]=='O'&&mp[s][j][k-1]==' '){
  //�ڽ� ��ġ�� ������ �迭�� ��ġ�� ���� ĳ������ ��ġ�̰� �� ������ �����̸� ĳ���͸� �������� �а� ���� ��ġ�� �������
 mp[s][j][k]='O';
 mp[s][j][k-1]='@';
 }
 else if(mp[s][j][k-1]=='O'){//ĳ���� ��ġ ���� �ڽ� ����Ҹ�
   mp[s][j][k]=' ';
   mp[s][j][k-1]='@';//ĳ���� �̵�
 }
 system("clear");
 print_map(s);
  }
    }
else if(x=='k'){//�տ��� �����̴� �Ŷ� ���⸸ �ٸ��� ������ �ڵ��� �˰��� ���´� �Ȱ���
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

else if(x=='l'){//���������� �Ȱ���
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
else if(x=='j'){//����������
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
void jump_stage(){//stage�� �ѱ�� ���� ���� �Լ���,���� �̿ϼ��� ������
  check_box=0;//������ ����� ���� ������ �о '$'�� �κ��� �ڽ� ��ġ�� �����ϴ� �迭�� ��쿡�� 'O'�϶� ���� a��� ���ڸ� �������Ѽ�
  //check_box�� 6�� �Ǹ� 6���� �Ȱ��� �� ��Ȳ���� �����ϰ�,�׷��� �Ǹ� ���� ���������� �Ѿ�� �ϴ� ���
for(j=1;j<N;j++)
   for(k=0;k<M;k++){
     if(mp[s][j][k]=='$'&&ospot[s][j][k]=='O')//���� ���� ���� a�� �������Ѽ�
       check_box++;
     for(i=0;i<5;i++){
       if(s==i&&check_box==box_place[i]){//�� ���� ���� �� ���� ���� ��쿡
          s++;//���������� �����ְ�
          system("clear");
          error_map(s);//���� ������ ������ Ȯ���ϰ�
          print_map(s);//���� ����� ��
          start=clock();//�ð��� �ʱ�ȭ ��
          undo_init(s);
          }
      }
if(s==5){//�� �� �ű� ������
  system("clear");
  printf("\n\n\n\n\n  C O N G R A T U A T E F O R C L E A R ! ! ! !\n\n\n\n\n\n");//���ϸ޽����� ����ϰ�
  exit(1);//���α׷��� ������
}
}
}
void exit_game(){
  system("clear");
  printf("\n\n S E E  Y O U  ");
  for(i=0;i<M;i++){//�̸��� ȭ�鿡 ��½�����
  printf("%c ",name[i]);
  if(name[i+1]=='\n'){
    printf(".....");
  break;
}
}
  printf("\n\n\n(Command) %c",x);
   exit(1);//�׷���� ���α׷��� ������
}
void start_game(){
  system("clear");
  printf("Start.....\n");//�����Ѵٴ� ���� �����
  printf("Input name: ");//�̸��� �Է��϶�� ��½�Ŵ
  for(i=0;i<10;i++){
  scanf("%c",&name[i]);//�̸��� ���Ͱ��� �����ؼ� �ִ� 10���� ���� �ް� �����Ǿ�����
  if(name[i]=='\n')
  break;
  }
  system("clear");
    scan_map();//�� ���Ͽ��� ���� �о� ������ ��
    error_map(s);//�� ���Ͽ� ������ �ִ��� Ȯ���ϰ�
    print_map(s);//������ ���ٸ� ���� ��½�Ŵ
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
  printf("h(����),j(�Ʒ�),k(��),l(������)\n");
  printf("u(undo)\nr(replay)\nn(new)\ne(exit)\ns(save)\nf(fileload)\n");
  printf("d(display help)\nt(top)\n\n\n(Command)%c",x);
}
void replay_game(){
  //stage�� ��Ÿ���� s���� �ʱ�ȭ ��Ű�� ���� ������ �����Ͽ��� ���� �ٽ� �о ���� stage�� �ش��ϴ� ���� �ٽ� ����ϰ� �ű⼭ ���� �����ϰ���
  system("clear");//ȭ�鿡�� �տ��� ��µ� ������ �� �� ����������
  printf("\n\n\n\n\n �� �� �� �� �� �� �� �� �� �� �� ��");
  system("clear");
  scan_map();//�ٽ� �� ���Ͽ��� ���� �о
  print_map(s);//stage�� �´� ���� ��½�����
}
void new_game(){
  //s=0���� ���������� �ʱ�ȭ �ϰ� �ð� �Լ��� �ٽ� �ʱ�ȭ �ؾߵǴµ� �ð� �Լ� �κ��� ���ذ� �ȵǼ� �ָ���
  //�׸��� ���� �ٽ� �о 1��° �ʺ��� �ٽ� ��µǵ��� ��
  system("clear");//�տ��� ��µ� ������ �� �� ����������
  scan_map();//�ٽ� �����Ͽ��� ���� �ް�
  s=0;//���������� �ʱ�ȭ�ϰ�
  start=clock();
  print_map(s);//���� �����
}
int main(){
  //��� ���� 5���� ������� �����ϰ� 5���� ������ ������ߵǴ� ���� ����ؼ� ¥�ߵ�(���� ���� ����ؼ� ������ ��� �ϴ� �������� ���ߵɵ� ��)
  //load�Լ��� �ٸ� �е��� ¥���� �Ÿ� ���ļ� �ϸ� �� ���� ���� �� ����
 //sokoban������ ������� �������� ���ٰ� �����ϴ� ����
 FILE *sk;
 sk=fopen("sokoban","w");//���ڹ� ������ ����� ���ؼ� ����
 start_game();
  start=clock();
  undo_init(s);

while(1){
  jump_stage();
x=getch();
if(x=='d'){//sokoban������ ���۹��� �˷���
  display_manual(x);
}
else if(x=='s'){//�ʿ��� ������ ������
  save=clock();
  save_map(s,save);
  system("clear");
  print_map(s);
  printf("%c",x);//s�� �� �� �� ��½�����
}
else if(x=='e'){//������ �����Ű�� ��ư��
  end=clock();
  save_map(s,end);
  exit_game();
}
else if(x=='h'||x=='j'||x=='k'||x=='l'){//ĳ���͸� �����̴� ��ư��
  undo_logging();
  move_map(x);
  jump_stage(s);
}
else if(x=='n'){//���ο� �������� �����ϰ� �ϴ� ��ư��
 new_game();
}
else if(x=='u'){//undo�� �����ϰ� �Ϸ��� �Լ������� ���� ���� �κ��� �����
 undo_delogging(); 
 system("clear");
 print_map(s);
}
else if(x=='r'){//���� ������������ �ٽ� �����ϰ� �ϴ� ��ư��
  replay_game();
}
}
}

