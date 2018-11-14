#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


struct node{
	struct node *next;
	int data;
};

struct node* create(int data){
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


struct node* find_pre(struct node* node_head, int pos){
	
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
	

struct node* find_index(struct node* node_head, int pos){
	
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

 
//attention please: the head node is labelled as one with pos = 0
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
	//warning:The node pointed by node_del_pre->next previously has not been released before return.
	return data_del;
}

//attention please: the tail node is labelled as one with rvspos = 0
int delete_rvsindex(struct node* &node_head, int rvspos){
	return delete_index(node_head, getlen(node_head)-1-rvspos);
}

struct node* rvslist(struct node* &node_head){
	int list_len = getlen(node_head);
	if (list_len == 1 || list_len == 0) return node_head;
	struct node* node_new_head = find_index(node_head,list_len-1);
	struct node* node_right;
	struct node* node_left;	
	while(list_len!=1){
		node_right = find_index(node_head,list_len-1);
		node_left  = find_pre(node_head,list_len-1);
		node_right->next = node_left;
		node_left->next = NULL;
		list_len--;
	}
	node_head->next = NULL;
	node_head = node_new_head;
	return node_head;
}


struct node* find_mid_node(struct node* node_head){
	int len = getlen(node_head);
	if (len % 2 == 0){
		struct node* node_err = (node*)malloc(sizeof(node));
		node_err->data = -1;
		return node_err;
	}else{
		return find_index(node_head,(len-1)/2);
	}
}

struct node* quick_init(int data0, int data1, int data2, int data3, int data4){
	struct node* node_head = create(data0);
	put_back(node_head,data1);
	put_back(node_head,data2);
	put_back(node_head,data3);
	put_back(node_head,data4);
	return node_head;
}

//attention please: the node with biggest (int)data must be the head node; 
//the tail node has the smallest (int)data.
int find_next_node_index_in_ordered(struct node* node_head, int compared_data){
	int index = 0;
	struct node* node_tmp = node_head;
	if (node_tmp->data <= compared_data) return 0;
	while(node_tmp->next != NULL){
		if ((node_tmp->data >= compared_data) && (node_tmp->next->data <= compared_data)){
			index++;
			return index;
		}
		index++;
		node_tmp = node_tmp->next;
	}
	return getlen(node_head);
}

int is_asc(struct node* node_head){
	struct node* node_tmp = node_head;
	int count = 0;
	while(node_tmp->data >= node_tmp->next->data){
		node_tmp = node_tmp->next;
		count++;
		if (count == getlen(node_head)-1) return 1;
	}
	return -1;
}

int merge_ordered(struct node* &node_head1,struct node* &node_head2){
	int ERROR_UNORDERED = -2;
	int ERROR_LEN_INVAL = -1;
	if (getlen(node_head1) == 1 || getlen(node_head2) == 1){
		return ERROR_LEN_INVAL;
	}
	if (getlen(node_head1) == 0 || getlen(node_head2) == 0){
		return ERROR_LEN_INVAL;
	}
	int need_rvs = 0;
	if (is_asc(node_head1)== -1) {
		rvslist(node_head1);
		if (is_asc(node_head1) == -1) return ERROR_UNORDERED;
		need_rvs = 1;
	}
		
	struct node* node_tmp = node_head2;
	while(node_tmp->next != NULL){
		int pos = find_next_node_index_in_ordered(node_head1,node_tmp->data);
		put_index(node_head1, pos, node_tmp->data);
		node_tmp = node_tmp->next;
	}
	int pos = find_next_node_index_in_ordered(node_head1,node_tmp->data);
	put_index(node_head1, pos, node_tmp->data);
	if (need_rvs) rvslist(node_head1);
	return getlen(node_head1);
}
		
	


	
	
int main(){
	
	struct node* node_head1 = quick_init(100,200,300,400,500);
	//printlist(node_head);
	//rvslist(node_head1);
	//printlist(node_head);
	
	
	struct node* node_head2 = quick_init(101,10,30,4020,5);
	merge_ordered(node_head1,node_head2);	
	printlist(node_head1);
	//cout<<find_next_node_index_in_ordered(node_head,300)<<endl;
	//cout<<find_next_node_index_in_ordered(node_head,100)<<endl;
	//cout<<find_next_node_index_in_ordered(node_head,31)<<endl;
	//cout<<find_next_node_index_in_ordered(node_head,2)<<endl;
	return 0;
}
	

