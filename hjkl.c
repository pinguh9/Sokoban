#include<stdio.h>
#include<stdlib.h>
#include<termio.h>

int getch(void)
{
    int ch;

    struct termios buf;
    struct termios save;

    tcgetattr(0, &save);
    buf = save;

    buf.c_lflag&=~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
 
	tcsetattr(0, TCSAFLUSH, &buf);

    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}

int main(void)
{
	int map[10][10]=
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1
	}, i, j; //map 배열과 i, j는 맵출력을 위해 설정
	int ax=1, ay=1;

	map[ax][ay] = 2;

		for(i=0; i<10; i++){ //map 출력 이건 파일 불러오기로 대체
			for(j=0; j<10; j++)
			{
				switch(map[i][j])
				{

					case 0:
						printf(" ");
						break;
					case 1:
						printf("#");
						break;
					case 2:
						printf("@");
						break;
					printf("%d\n", map[i][j]);
				}
			}
			if(j=9)
				printf("\n");
		}

	int input_char, c; //s는 빈칸으로서 캐릭터와의 자리를 바꾸기 위한것임

		input_char = getch();
		if(input_char == 'h'){
			if(map[i][j-1][k] == 1)

			c = map[ax][ay];
			map[ax][ay] = map[i][j-1];
			map[i][j-1] = c;
		}

		else if(input_char == 'j'){
			c = map[ax][ay];
			map[ax][ay] = map[i+1][j];
			map[i+1][j] = c;
		}

		else if(input_char == 'k'){
			c = map[ax][ay];
			map[ax][ay] = map[i-1][j];
			map[i-1][j] = c;
		}

		else if(input_char == 'l'){
			c = map[ax][ay];
			map[ax][ay] = map[i][j+1];
			map[i][j+1] = c;
		}

		for(i=0; i<10; i++){ //map 출력 이건 파일 불러오기로 대체
			for(j=0; j<10; j++)
			{
				switch(map[i][j])
				{
					case 0:
						printf(" ");
                        break;
                    case 1:
						printf("#");
                        break;
					case 2:
                        printf("@");
						break;
                    printf("%d\n", map[i][j]);
				}
			}
			if(j=9)
				printf("\n");
		}


	return 0;
}
