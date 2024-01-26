#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

int menu;
int menu_status;
char nama[200];
char role[200];
char selected_enemy[200];
int gold = 0;
int exp = 0;
int level = 1;
int damage;
int health;
int health1;
int pil_fight;

int save = 0;
int data_save;

int damage_goblin = 5, health_goblin = 20, exp_goblin = 10, gold_goblin = 5;
int damage_orc = 3, health_orc = 25, exp_orc = 12, gold_orc = 7;
int damage_wizard = 10, health_wizard = 15, exp_wizard = 15, gold_wizard = 10;

int health_enemy ;
int damage_enemy ;
int get_gold ;
int get_exp ;

void new_game(){
	system("cls");
	FILE *fp;
	fp = fopen("data game.txt", "r");
	fscanf(fp, "%d", &save);
	fclose(fp);
	
	if(save==0){
		printf("1. Start New Game\n>> ");
	}
	else if(save==1){
		printf("1. Start New Game\n2. Continue Game\n>> ");
	}
	else{
		new_game();
	}
}

void role1 (){
	printf("Choose your class[Warrior|Rogue|Archer] :");
	scanf("%s",role);
	if(strcmp(role, "Warrior")==0){
		damage=5;
		health = 150, health1 = 150;
	}
	else if(strcmp(role, "Rogue")==0){
		damage=10;
		health = 75, health1 = 75;
	}
	else if(strcmp(role, "Archer")==0){
		damage=7;
		health = 100, health1 = 100;
	}
	else{
		role1();
	}
}

void menuStatus(){
	system("cls");
	printf("%s's Status\n===============\n",nama);
	printf("Level %d\n",level);
	printf("Class : %s\n",role);
	printf("Gold : %d\n",gold);
	printf("Exp  : %d/100\n",exp);
	printf("Health : %d/%d\n",health1,health);
	printf("1. Fight\n");
	printf("2. Heal\n");
	printf("3. Save\n");
	printf("4. Quit\n>> ");
	scanf("%d",&menu_status);
}

void fight_menu(){
	system("cls");
	printf("Fight Menu\n===============\n");
	printf("1. Goblin\n");
	printf("2. Orc\n");
	printf("3. Wizard\n");
	printf("4. Back\n>> ");
	scanf("%d",&pil_fight);
}

void heal_menu(){
	if (health==health1){
		printf("You're already at max health!\n");
	}
	else if(gold<20){
		printf("You don't have enough gold!\n");
	}
	else{
		printf("Do you want to heal yourself for 20 golds?\n");
		printf("1. Yes\n");
		printf("2. No\n");
		int pil;
		scanf("%d",&pil);
		if(pil==1){
			gold-=20;
			health1 = health;
			printf("Healed!!\n");
		}
		else if(pil==2){

		}
		else{
			heal_menu();
		}
	}
	printf("Press any key to continue...\n");
	getchar();
}

void enemy(){
	if (pil_fight==1){
		strcpy(selected_enemy, "Goblin");
		health_enemy = health_goblin;
		damage_enemy = damage_goblin;
		get_gold = gold_goblin;
		get_exp = exp_goblin;
	}
	else if (pil_fight==2){
		strcpy(selected_enemy, "Orc");
		health_enemy = health_orc;
		damage_enemy = damage_orc;
		get_gold = gold_orc;
		get_exp = exp_orc;
	}
	else if (pil_fight==3){
		strcpy(selected_enemy, "Wizard");
		health_enemy = health_wizard;
		damage_enemy = damage_wizard;
		get_gold = gold_wizard;
		get_exp = exp_wizard;
	}
}

void fight(){
	system("cls");
	if (pil_fight==1|pil_fight==2|pil_fight==3){
		printf("%s\n",selected_enemy);
		printf("Health : %d\n",health_enemy);
		printf("Damage : %d\n\n",damage_enemy);
		printf("%s\n",nama);
		printf("Health : %d\n",health1);
		printf("Damage : %d\n\n",damage);
		printf("1. Attack\n");
		printf("2. Run\n>> ");
		int pil;
		int enemy_dead;
		int hero_dead;
		int run_away;
		scanf("%d",&pil);
		if (pil==1){
			health_enemy -= damage;
			if (health_enemy<=0){
				gold += get_gold;
				exp += get_exp;
				printf("You won!\n");
				printf("You gained %d gold(s) and %d exp(s)\n",get_gold, get_exp);
				if (exp>=100){
					printf("You've leveled up!\n");
					exp-=100;
					level+=1;
				}
				enemy_dead = 1;
				printf("Press any key to continue...\n");
				getchar();
			}
			if (enemy_dead != 1){
				health1 -= damage_enemy;
				if (health1<=0){
					printf("You lose!\n");
					printf("You lost all your golds and exps\n");
					gold = 0;
					exp = 0;
					health1 = health;
					hero_dead = 1;
					printf("Press any key to continue...\n");
					getchar();
				}
			}
		}
		else if (pil==2){
			run_away = 1;
			enemy();
			printf("You ran away!\n");
			printf("Press any key to continue...\n");
			getchar();
		}
		if (hero_dead == 1|run_away == 1){
			
		}
		else if (enemy_dead != 1){
			fight();
		}
	}
}

void fight_mix(){
	fight_menu();
	if (pil_fight==1|pil_fight==2|pil_fight==3){
		enemy();
		fight();
		getchar();
	}
	if (pil_fight==1|pil_fight==2|pil_fight==3){
		fight_mix();
	}
}

void game_save(){
	save = 1;
	FILE *fp;
	fp = fopen("data game.txt", "w");
	fprintf(fp, "%d %s %d %s %d %d %d", save, nama, level, role, gold, exp, health1);
	fclose(fp);
	printf("Saved Successfully!!\n");
	printf("Press any key to continue...\n");
	getchar();
}

void menu_game(){
	menuStatus();
	if (menu_status==1){
		fight_mix();
		if (pil_fight==4){
			menu_game();
		}
	}
	else if (menu_status==2){
		heal_menu();
		getchar();
		menu_game();
	}
	else if (menu_status==3){
		game_save();
		getchar();
		menu_game();
	}
	else if (menu_status==4){
		
	}
	else{
		menu_game();
	}
}

int main(){

	while(true){
		new_game();
		scanf("%d",&menu);
		if(menu==1){
			printf("Input your character's name  : ");
			scanf("%s",nama);
			role1();
			menu_game();
			if (menu_status==4){
				break;
			}
		}
		else if (menu==2){
			FILE *fp;
			fp = fopen("data game.txt", "r");
			fscanf(fp, "%d %s %d %s %d %d %d", &save, nama, &level, role, &gold, &exp, &health1);
			fclose(fp);
			if(strcmp(role, "Warrior")==0){
				damage=5;
				health = 150, health1 = 150;
			}
			else if(strcmp(role, "Rogue")==0){
				damage=10;
				health = 75, health1 = 75;
			}
			else if(strcmp(role, "Archer")==0){
				damage=7;
				health = 100, health1 = 100;
			}
			menu_game();
			if (menu_status==4){
				break;
			}
		}
	}
	
	return 0;
}


