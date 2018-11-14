#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


struct node{
	struct node *next;
	int data;
};

node* create(int data){
	node *node_head = (node*)malloc(sizeof(node));
	node_head->next = NULL;
	node_head->data = data;
	return node_head;
}



int getlen(struct node* node_head){
	int i = 0;
	node *node_tmp = (node*)malloc(sizeof(node));
	node_tmp = node_head;
	while(node_tmp != NULL){
		i++;
		node_tmp = node_tmp->next;
	}
	return i;
}

int put_back(struct node* node_head, int data){
	node *node_tmp = (node*)malloc(sizeof(node));
	node_tmp = node_head;
	int i = 0;
	while(node_tmp->next != NULL){
		i++;
		node_tmp = node_tmp->next;
	}
	node *node_insert = (node*)malloc(sizeof(node));
	node_insert->data = data;
	node_insert->next = NULL;
	node_tmp->next = node_insert;
	return node_insert->data;
	
}

void printlist(struct node * node_head){
	int LinkedListLen = 0;
	LinkedListLen = getlen(node_head);
	printf("This linkedList is %d in length. \n",LinkedListLen);
	struct node* node_tmp = (node*)malloc(sizeof(node));
	if (node_head == NULL){
		printf("sorry, node_head is NULL !\n");
		return;
	}
	node_tmp = node_head;
	
	int index = 0;
	while(node_tmp->next != NULL){
		printf("node[%d] is %d \n", index, node_tmp->data);
		index++;
		node_tmp = node_tmp->next;
	}
	printf("node[%d] is %d \n", index, node_tmp->data);
}


node* find_pre(struct node* node_head, int pos){
	
	struct node* node_tmp = (node*)malloc(sizeof(node));
	node_tmp->data = -1;

	if (pos > getlen(node_head)){
		return node_tmp;
	}	
	int i = 0;
	node_tmp = node_head;
	int size = getlen(node_head);
	int poss = pos - 1;
	while( i!= size){
		if (i == poss){
			return node_tmp;
		}
		node_tmp = node_tmp->next;
		i++;
	}
	node_tmp->data = -1;
	return node_tmp;
}
	

node* find_index(struct node* node_head, int pos){
	
	struct node* node_tmp = (node*)malloc(sizeof(node));
	if (pos >= getlen(node_head)){
		node_tmp->data = -1;
		return node_tmp;
	}
	
	node_tmp = find_pre(node_head, pos+1);
	return node_tmp;
}


int put_index(struct node* &node_head, int pos, int data){
	if (pos == getlen(node_head)){
		return put_back(node_head,data);
	}
	if (pos > getlen(node_head)){
		return -1;
	}
	
	struct node *node_tmp =  (node*)malloc(sizeof(node));
	if (pos == 0){
		node_tmp->data = data;
		node_tmp->next = node_head;
		node_head = node_tmp;
		return node_head->data;
	}
		
	node_tmp->data = data;
	struct node *node_pre = find_pre(node_head,pos);
	if (node_pre->data == -1){
		return -1;
	}
	node_tmp->next = node_pre->next;
	node_pre->next = node_tmp;
	return node_tmp->data;
}

 
int delete_index(struct node* &node_head, int pos){
	if (pos >=getlen(node_head)){
		return -1;
	}
	if (pos == 0){
		int del_data = node_head->data;
		if (node_head->next == NULL){
			node_head = NULL;
			return 0;
		}
		node_head = node_head->next;
		return del_data;
	}
	struct node* node_del_pre = find_pre(node_head, pos);
	int data_del = node_del_pre->next->data;
	node_del_pre->next = node_del_pre->next->next;
	return data_del;
}






int main(){
	
	struct node *node_head = create(100);
	put_index(node_head, 1,1000);
	put_index(node_head,2,3333);
	put_index(node_head, 1,1000);
	put_index(node_head,2,3333);
	put_index(node_head,0,5151);
	delete_index(node_head,0);
	delete_index(node_head,4);

	delete_index(node_head,1);
	delete_index(node_head,1);
	delete_index(node_head,1);
	delete_index(node_head,1);
	delete_index(node_head,0);
	
	printlist(node_head);
	
	
	

	return 0;
}
	

