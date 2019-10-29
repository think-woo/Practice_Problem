#include <stdio.h> //fopen(), fclose(), fscanf()
#include <stdlib.h> //malloc(), free();

#pragma pack(push,1)
struct goods{
	char name[10]; //��ǰ�̸�
	int num; //��ǰ��ȣ
	int price; //��ǰ����
	double rate1; //1�� �� ���� ������
	double rate2; //2�� �̻� �� ���� ������
	int buyPrice; //������ ��ǰ�� �� ����
	int buyNum; //������ ��ǰ�� �� ����
};
#pragma pack(pop)

int main(){

	struct goods *g[7]; //��ǰ ����ü
	struct goods *temp; //�ӽú���
	int goodsldx, goodsNum; //������ ��ǰ ��ȣ, ��ǰ ����
	int MAX_BUY = 50; //�� �� �ִ� ��ǰ �ִ� ��ǰ ����
	int i, j;

	FILE *fp = fopen("goods_list.txt", "r");
	
	//��ǰ ����
	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		g[i] = malloc(sizeof(struct goods));
		fscanf(fp, "%s %d %d %lf %lf", g[i]->name, &g[i]->num, &g[i]->price, &g[i]->rate1, &g[i]->rate2);
		g[i]->buyPrice = 0;
		g[i]->buyNum = 0;
	}

	//��ǰ ����Ʈ ���
	printf("*** Item ***\n");
	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		printf("%d. %s\n", g[i]->num, g[i]->name);
	}

	//�ִ� ������ŭ ��ǰ ���� ����
	while(MAX_BUY > 0){
		printf("Select Item (1~7) ? =");
		scanf("%d", &goodsldx);

		printf("Input the number of item: ");
		scanf("%d", &goodsNum);

		if(MAX_BUY - goodsNum < 0){
			continue;
		}
		else{
			if(goodsNum == 1){ //��ǰ ������ 1�� �϶�, ���η� ����
				g[goodsldx-1]->buyPrice = g[goodsldx-1]->price * goodsNum * g[goodsldx-1]->rate1;
				g[goodsldx-1]->buyNum = goodsNum;
			}
			else{ //��ǰ ������ 2�� �̻� �϶�, ���η� ����
				g[goodsldx-1]->buyPrice = g[goodsldx-1]->price * goodsNum * g[goodsldx-1]->rate2;
				g[goodsldx-1]->buyNum = goodsNum;
			}

			MAX_BUY -= goodsNum;
		}
	}
	//������ ��ǰ ���� ���
	printf("*** Price of Goods ***\n");
	for(i=0; i<sizeof(g)/sizeof(struct goods*); i++){
		printf("%s = %d\n", g[i]->name, g[i]->buyPrice);
	}

	//������ ��ǰ ���� ���(��������)
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

	//������ ��ǰ ���� ���(��������)
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