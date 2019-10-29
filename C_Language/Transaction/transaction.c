#include <stdio.h> //fopen(), fclose(), fscanf()
#include <stdlib.h> //malloc(), free();

#pragma pack(push,1)
struct goods{
	char name[10]; //상품이름
	int num; //상품번호
	int price; //상품가격
	double rate1; //1개 살 때의 할인율
	double rate2; //2개 이상 살 때의 할인율
	int buyPrice; //구매한 제품의 총 가격
	int buyNum; //구매한 제품의 총 개수
};
#pragma pack(pop)

int main(){

	struct goods *g[7]; //상품 구조체
	struct goods *temp; //임시변수
	int goodsldx, goodsNum; //선택한 상품 번호, 상품 갯수
	int MAX_BUY = 50; //고를 수 있는 상품 최대 상품 갯수
	int i, j;

	FILE *fp = fopen("goods_list.txt", "r");
	
	//상품 설정
	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		g[i] = malloc(sizeof(struct goods));
		fscanf(fp, "%s %d %d %lf %lf", g[i]->name, &g[i]->num, &g[i]->price, &g[i]->rate1, &g[i]->rate2);
		g[i]->buyPrice = 0;
		g[i]->buyNum = 0;
	}

	//상품 리스트 출력
	printf("*** Item ***\n");
	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		printf("%d. %s\n", g[i]->num, g[i]->name);
	}

	//최대 갯수만큼 상품 구매 가능
	while(MAX_BUY > 0){
		printf("Select Item (1~7) ? =");
		scanf("%d", &goodsldx);

		printf("Input the number of item: ");
		scanf("%d", &goodsNum);

		if(MAX_BUY - goodsNum < 0){
			continue;
		}
		else{
			if(goodsNum == 1){ //상품 갯수가 1개 일때, 할인률 적용
				g[goodsldx-1]->buyPrice = g[goodsldx-1]->price * goodsNum * g[goodsldx-1]->rate1;
				g[goodsldx-1]->buyNum = goodsNum;
			}
			else{ //상품 갯수가 2개 이상 일때, 할인률 적용
				g[goodsldx-1]->buyPrice = g[goodsldx-1]->price * goodsNum * g[goodsldx-1]->rate2;
				g[goodsldx-1]->buyNum = goodsNum;
			}

			MAX_BUY -= goodsNum;
		}
	}
	//선택한 상품 가격 출력
	printf("*** Price of Goods ***\n");
	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		printf("%s = %d\n", g[i]->name, g[i]->buyPrice);
	}

	//선택한 상품 가격 출력(오름차순)
	printf("*** Price of Goods (Ascending Order) ***\n");
	
	for(i=0; i<sizeof(g)/sizeof(struct goods*)-1; i++){
		for(j=0; j<sizeof(g)/sizeof(struct goods*)-1-i; j++){
			if(g[j]->buyPrice > g[j+1]->buyPrice){
				temp = g[j];
				g[j] = g[j+1];
				g[j+1] = temp;
			}
		}
	}

	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		printf("%s = %d\n", g[i]->name, g[i]->buyPrice);
	}

	//선택한 상품 갯수 출력(오름차순)
	printf("*** Number of Goods (Ascending Order) ***\n");
	
	for(i=0; i<sizeof(g)/sizeof(struct goods*)-1; i++){
		for(j=0; j<sizeof(g)/sizeof(struct goods*)-1-i; j++){
			if(g[j]->buyNum > g[j+1]->buyNum){
				temp = g[j];
				g[j] = g[j+1];
				g[j+1] = temp;
			}
		}
	}

	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		printf("%s = %d\n", g[i]->name, g[i]->buyNum);
	}
	
	fclose(fp);

	return 0;
	
}