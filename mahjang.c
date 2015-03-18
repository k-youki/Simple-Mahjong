#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define color(cc) printf("\33[3%dm",cc);
#define iti(aa,bb)  printf("\x1b[%d;%dH",aa,bb);

void out_put(int num);
void sort(int *pt);
void guid(int j);
void rinshan(int *pt, int *st);
void haipai(int *pt, int *st);
int yama(int *pt);
int hantei(int *pt);
int check(int *pt, int num);
void Kan(int *pt);
void tenpai(int *pt);
int tenpai_hantei(int *pt);
void AA(int j);
void file_out(int *pt);

//使った牌はstrが1になる
//136 = 牌未指定状態

int main(void)
{
  int i, val, zan, get, t;
  int agarihantei;
  int j = 0;
  int tehai[14] = {136};
  int tehai2[14] = {136}; 
  int kawa[100] = {136};
  int kan[4] = {136};
  int wanpai[14] = {136};
  int str[136] = {0};

  srand((unsigned)time(NULL));
  
  rinshan(wanpai, str);
  haipai(tehai, str);
  
  while(1){
    system("clear");
    
    sort(tehai);
    guid(j);
  
    iti(8,3);
    printf("手牌　");
    for(i=0; i<13; i++)
      out_put(tehai[i]);
    
    iti(2,3);
    printf("ドラ　");
    out_put(wanpai[4]);
       
    iti(4,3);
    printf("河　　");
    for(i=0; kawa[i] != '\0'; i++){
      iti(4+i/6,9+4*(i%6));
      out_put(kawa[i]);  
    }
    
    if(j == 18){
      iti(14,38);
      printf("流 局\n");
      iti(23,0);
      return 0;
    }

    AA(j);

    for(i=0; i<1; i++){ //自摸牌判定
      val = rand() % 136;
      if(str[val] == 0){
	tehai[13] = val; //手牌配列13番目→自摸牌
	str[val] = 1;
      }else
	i--;
    }
    
    iti(11,3);
    printf("自摸　");
    out_put(tehai[13]);

    for(i=0; i<14; i++)
      tehai2[i] = tehai[i];

    sort(tehai2); //手牌をソートしてから判定関数へ
    agarihantei = hantei(tehai2); //上がり判定
    Kan(kan);
    tenpai(tehai2);
    
    for(i=0; i<1; i++){
      iti(14,3);
      printf("何番目の牌を切る？  ");
      scanf("%d", &get);
      if(0>get || get>15){
	iti(16,3);
	printf("input rule>> 0~13\n");
	i--;
      }else if(agarihantei == 1 && get == 14){
	iti(14,40);
	printf("上がり\n");
	file_out(tehai2);
	iti(23,0);
	return ;
      }else if(agarihantei == 0 && get == 14){
	iti(12,40);
	printf("上がれません");
	i--;
      }else if(get == 15){
	if(kan[0] != 136){
	  iti(17,20);
	  printf("樌可能な番号");
	  for(t=0; kan[t] != 136; t++)
	    printf("3%d", kan[t]);
	}
	i--;
      }else if(get == 0){
	kawa[j] = tehai[13];
	tehai[13] = 136;
      }else if(get > 0 && get < 14){
	kawa[j] = tehai[get-1];
	tehai[get-1] = tehai[13];
	tehai[13] = 136; //初期化
      }
    }
    
    j++;
  }
  return ;
}
  
void out_put(int num)
{
  if(num >= 0 && num < 36){
    printf("%d",num / 4 + 1);
    color(1);
    printf("萬");
  }else if(num > 35 && num < 72){
	printf("%d",(num-36) / 4 + 1);
    color(4);
	printf("筒");
  }else if(num > 71 && num < 108){
    printf("%d", (num-72) / 4 + 1);  
    color(2);
    printf("索");
  }
  if(num >= 108 && num <= 111)
    printf("東 ");
  else if(num >= 112 && num <= 115)
    printf("南 ");
  else if(num >= 116 && num <= 119)
    printf("西 ");
  else if(num >= 120 && num <= 123)
    printf("北 ");
  else if(num >= 124 && num <= 127)
    printf("白 ");
  else if(num >= 128 && num <= 131){
    color(2);
    printf("發 ");
  }
  else if(num >= 132 && num <= 135){
    color(1);
    printf("中 ");
  }
  color(7);
  printf(" ");
}

void sort(int *pt)
{
  int num;
  int i, j;
  
  for(i=0; i<13; i++){
    for(j=i; j<13; j++){
      if(pt[j] < pt[i]){
	num = pt[i];
	pt[i] = pt[j];
	pt[j] = num;
      }
    }
  }
}

void guid(int j)
{
  int i;
  
  color(6);
  for(i=1; i<14; i++){
    iti(9,5+i*4);
    printf("%d\n", i);
  }
  iti(12,9);
  printf("0\n");
  iti(21,3);
  printf("樌未実装\n");
  iti(22,3);
  printf("ドラは表示牌\n");
  iti(23,3);
  printf("14:上がり\n");
  iti(5,65);
  printf("%d順目\n",j+1);
  iti(6,65);
  printf("残り牌:%d\n",17-j);
  iti(3,65);
  printf("東一局 東家");
  color(7);
}

void rinshan(int *pt, int *st)
{
  int i, val;
  
  for(i=0; i<14; i++){
    val = rand() % 136;
    if(st[val] == 0){
      pt[i] = val;
      st[val] = 1;
    }else if(st[val] != 0)
      i--;
  }
}

void haipai(int *pt, int *st)
{
  int i, val;
  
  for(i=0; i<13; i++){ 
    val = rand() % 136;
    if(st[val] == 0){
      pt[i] = val;
      st[val] = 1;
    }else if(st[val] != 0)
      i--;
  }
} 

int yama(int *pt)
{
  int i, j=0;
  
  for(i=0; i<136; i++){
    if(pt[i] == 0)
      j++;
  }
   iti(17, 65);
  printf("残り山:%d\n", j);

  return j;
}

int hantei(int *pt)
{
  int i, j, t, p, p2;
  int H1, H2, H3;
  int tmp = 0;
  int n = 0;
  int num = 0;
  int bt[5] = {0};
  int tehai2[14] = {0};
  int atama = 0;
   
  for(p=0; p<14; p++){
    for(p2=p+1; p2<14; p2++){
      if(pt[p]/4 == pt[p2]/4){
	H1 = check(tehai2, pt[p]);
	H2 = check(tehai2, pt[p2]);
	if(H1 == 0 && H2 == 0){ 
	  iti(19,65);
	  printf("雀頭 %d,%d" ,p+1, p2+1);
	  tehai2[12] = pt[p];
	  tehai2[13] = pt[p2];
	  for(i=0; i<14; i++){ //順子判定のループ
	    for(j=0; j<14; j++){
	      if(pt[i] <= 108){
		if(pt[i]/4+1 == pt[j]/4){
		  if((pt[i]/4+1)%9 != 0 && (pt[j]/4+1)%9 != 0){ 
		    for(t=0; t<14; t++){
		      if(pt[i]/4+2 == pt[t]/4){
			H1 = check(tehai2, pt[i]);
			H2 = check(tehai2, pt[j]);
			H3 = check(tehai2, pt[t]);
			if(H1 == 0 && H2 == 0 && H3 == 0){
			  iti(20+n, 65);
			  printf("順子 %d,%d,%d", i+1, j+1, t+1);
			  bt[n] = 2; //順子=2
			  n++;
			  tehai2[tmp] = pt[i];
			  tehai2[tmp+1] = pt[j];
			  tehai2[tmp+2] = pt[t];
			  tmp += 3;
			}
		      }
		    }
		  }
		}  
	      }
	    }
	  }
	  for(i=0; i<14; i++){
	    if(pt[i]/4 == pt[i+1]/4){
	      for(j=i+2; j<14; j++){
		if(pt[i]/4 == pt[j]/4){
		  H1 = check(tehai2, pt[i]);
		  H2 = check(tehai2, pt[i+1]);
		  H3 = check(tehai2, pt[j]);
		  if(H1 == 0 && H2 == 0 && H3 ==0){
		    iti(20+n, 65);
		    printf("暗刻 %d,%d,%d", i+1, i+2, j+1);
		    bt[n] = 3; //暗刻=3
		    n++;
		    tehai2[tmp] = pt[i];
		    tehai2[tmp+1] = pt[i+1];
		    tehai2[tmp+2] = pt[j];
		    tmp += 3;
		  }
		}
	      }
	    }
	  }
	  if(n == 4)
	    return 1;
	}
      }
    }
  }
  
  return 0;
}

int check(int *pt, int num)
{
  int i;
  int tmp = 0;
  
  for(i=0; i<14; i++){
    if(num == pt[i])
      tmp = 1;
  }
  
  return tmp;
}

void Kan(int *pt){
  int i, j;
  int num = 0;
  
  for(i=0; i<14; i++){
    for(j=i; j<14; j++){
      if(pt[i]/4 == pt[j]/4)
	num++;
    }
    if(num == 3){
      pt[i] = i;
    }
  }
}

void tenpai(int *pt)
{
  int i, j = 0;
  int bt[15] = {136};
  int num, tmp;
  int p1 ,p2;
  int paisuu = 0;

  for(i=0; i<14; i++)
    bt[i] = pt[i]; //手牌のコピー
  
  for(i=0; i<34; i++){
    bt[14] = i*4;
    for(p1=0; p1<14; p1++){
      for(p2=0; p2<14; p2++){
	if(bt[p2] < bt[p1]){
	  tmp = bt[i];
	  bt[i] = bt[j];
	  bt[j] = tmp;
	}
      }
    }
    num = tenpai_hantei(bt);
    if(num == 1){
      iti(8,65);
      color(3);
      printf("聴 牌\n");
      iti(9,65);
      color(8);
      printf("待ち牌\n");
      iti(10+j,65);
      out_put(i*4);
      j++;
    }
  }
}

int tenpai_hantei(int *pt)
{
  int i, j, t, p, p2;
  int H1, H2, H3;
  int tmp = 0;
  int n = 0;
  int num = 0;
  int bt[5] = {0};
  int tehai2[14] = {0};
  int atama = 0;
   
  for(p=0; p<15; p++){
    for(p2=p+1; p2<15; p2++){
      if(pt[p]/4 == pt[p2]/4){
	H1 = check(tehai2, pt[p]);
	H2 = check(tehai2, pt[p2]);
	if(H1 == 0 && H2 == 0){ 
	  tehai2[12] = pt[p];
	  tehai2[13] = pt[p2];
	  for(i=0; i<15; i++){ //順子判定のループ
	    for(j=0; j<15; j++){
	      if(pt[i] <= 108){
		if(pt[i]/4+1 == pt[j]/4){
		  if((pt[i]/4+1)%9 != 0 && (pt[j]/4+1)%9 != 0){ 
		    for(t=0; t<15; t++){
		      if(pt[i]/4+2 == pt[t]/4){
			H1 = check(tehai2, pt[i]);
			H2 = check(tehai2, pt[j]);
			H3 = check(tehai2, pt[t]);
			if(H1 == 0 && H2 == 0 && H3 == 0){
			  bt[n] = 2; //順子=2
			  n++;
			  tehai2[tmp] = pt[i];
			  tehai2[tmp+1] = pt[j];
			  tehai2[tmp+2] = pt[t];
			  tmp += 3;
			}
		      }
		    }
		  }
		}  
	      }
	    }
	  }
	  for(i=0; i<15; i++){
	    if(pt[i]/4 == pt[i+1]/4){
	      for(j=i+2; j<15; j++){
		if(pt[i]/4 == pt[j]/4){
		  H1 = check(tehai2, pt[i]);
		  H2 = check(tehai2, pt[i+1]);
		  H3 = check(tehai2, pt[j]);
		  if(H1 == 0 && H2 == 0 && H3 ==0){
		    bt[n] = 3; //暗刻=3
		    n++;
		    tehai2[tmp] = pt[i];
		    tehai2[tmp+1] = pt[i+1];
		    tehai2[tmp+2] = pt[j];
		    tmp += 3;
		  }
		}
	      }
	    }
	  }
	  if(n == 4)
	    return 1;
	}
      }
    }
  }
  
  return 0;
}

void AA(int j)
{
  int val;
  
   iti(30,30);
   
    if(j==0)
      printf("クソ配牌だな>v('ω')v");
    else if(j>=1 && j<=18){
      val = rand() % 20;
      if(val==0)
	printf("神ヅモですわ>(^ー^)");
      else if(val==1)
	printf("kzしかいないなこの手牌('ω')凸");
      else if(val==2)
	printf("あゆみィ('ω'#)");
      else if(val==3)
	printf("スマブラァ");
      else if(val==4)
	printf("関東最強！w");
      else if(val==5)
	printf("(っ'ω'c)むにっと");
      else if(val==6)
	printf("とんとろとろとん(-ω-`)");
      else if(val==7)
	printf("三(^o^)ﾉ");
      else if(val==8)
	printf("これは役満ですわ！w");
      else if(val==9)
	printf("かとりょートイレ行こうぜー(^o^)/");
      else if(val==10)
	printf("七対子実装してません！！w");
      else if(val==11)
	printf("国士無双実装してません！！w");
      else if(val==12)
	printf("染めようぜ！w('ω')");
      else if(val==13)
	printf("役の実装間に合いませんでした！w");
      else if(val==14)
	printf("I am the assasin >(黒餅)");
      else if(val==15)
	printf("七時半！！");
      else if(val==16)
	printf("雀龍門マジック実装してません！w");
      else if(val==17)
	printf("平和型しか対応してません<(^o^)>");
      else if(val==18)
	printf("まだバグが多いですL('w')ﾍ");
      else if(val==19)
	printf("Special Thanks for You-Die");
    }
}

void file_out(int *pt)
{
  FILE *fp;
  int i;
  
  fp=fopen("tehai.txt","w");
  
  for(i=0; i<14; i++){
    fprintf(fp,"%d\n", pt[i]);
  }
  fclose(fp);
}
