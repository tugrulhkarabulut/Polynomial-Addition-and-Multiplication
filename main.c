#include <stdio.h>
#include <stdlib.h>
/*
	IMPLEMENTING LINKED LISTS TO CALCULATE THE SUM
	AND THE PRODUCT OF GIVEN TWO POLYNOMIAL FUNCTIONS
	
*/

// Creating a polynomial term struct
typedef struct 
{
	int coefficient;
	int degree;
}polynomial_term;



// Node structure of linked list
typedef struct node 
{
	polynomial_term poly_term;
	struct node *next;
}node;

typedef node *node_ptr;
typedef node **node_ptr_ref;

typedef struct list 
{
	node_ptr list;
}list;


list *create_list(list *pl)
{
  	pl = (list *)malloc(sizeof(list));
  	pl -> list = 0;
  	return pl;
}

node_ptr create_node(int coeff, int degree) {
	node_ptr term = (node_ptr)malloc(sizeof(node_ptr));
	term -> poly_term.coefficient = coeff;
	term -> poly_term.degree = degree;
	return term;
}


// Inserting the node according to its polynomial term's degree
void add_term(node_ptr term, list *pl) {
	node_ptr_ref first_item = &(pl -> list);
	
	// If the node must be the first element of the list
	if (*first_item == 0 || (*first_item) -> poly_term.degree < term -> poly_term.degree) {
		term -> next = (*first_item);
		(*first_item) = term;
		return;
	}
	
	// Iterate over the list to find the node's right place in the middle or the end
	node_ptr iterator = *first_item;
	while (iterator -> next != 0) {
		if (iterator -> next -> poly_term.degree < term -> poly_term.degree)
			break;
		iterator = iterator -> next;
	}
	term -> next = iterator -> next;
	iterator -> next = term;
	return;
}


void remove_term(int degree, list *pl) {
	if (pl -> list -> poly_term.degree == degree) {
		pl -> list = pl -> list -> next;
		return;
	}
	node_ptr current = pl -> list, prev = 0;
	while(current != 0 && current -> poly_term.degree != degree) {
		prev = current;
		current = current -> next;	
	}
	if (current == 0) return;
	prev -> next = current -> next;
	free(current);
}

void display_list(list *pl);

// Adding two polynomial functions
list *add_poly(list *P1, list *P2, list *P_result) {
	node_ptr iterator_p1 = P1 -> list, iterator_p2 = P2 -> list, removed_p1 = 0, removed_p2 = 0;
	
	// If one of the lists is empty return the other one
	if (iterator_p1 == 0) return P2;
	if (iterator_p2 == 0) return P1;
	
	// Look for the terms with the same degrees and add them. After adding them, remove them from their original polynoms
	while (iterator_p1) {
		iterator_p2 = P2 -> list;
		while (iterator_p2) {
			if (iterator_p1 -> poly_term.degree == iterator_p2 -> poly_term.degree) {
				add_term(create_node(iterator_p1 -> poly_term.coefficient + iterator_p2 -> poly_term.coefficient, iterator_p1 -> poly_term.degree), P_result);
				removed_p1 = iterator_p1;
				removed_p2 = iterator_p2;
				break;
			}
			iterator_p2 = iterator_p2 -> next;
		}
		iterator_p1 = iterator_p1 -> next;
		
		if (removed_p1) {
			remove_term(removed_p1 -> poly_term.degree, P1);
			removed_p1 = 0;
		}
			
		if (removed_p2) {
			remove_term(removed_p2 -> poly_term.degree, P2);
			removed_p2 = 0;
		}
		
	}
	
	node_ptr iterator_1 = P1 -> list, iterator_2 = P2 -> list;
	
	
	// Add the remaining terms which has unique degrees to the resulting polynom
	while(iterator_1 -> next != 0) {
		add_term(create_node(iterator_1 -> poly_term.coefficient, iterator_1 -> poly_term.degree), P_result);
		iterator_1 = iterator_1 -> next;
	}
	
	
	while(iterator_2 != 0) {
		add_term(create_node(iterator_2 -> poly_term.coefficient, iterator_2 -> poly_term.degree), P_result);
		iterator_2 = iterator_2 -> next;
	}
	
	return P_result;
}

list *mult_poly(list *P1, list *P2, list *P_result) {
	node_ptr iterator_p1 = P1 -> list, iterator_p2 = P2 -> list;
	
	// Multiply every element of P1 with P2
	while (iterator_p1 != 0) {
		iterator_p2 = P2 -> list;
		while (iterator_p2 != 0) {
			add_term(create_node(iterator_p1 -> poly_term.coefficient * iterator_p2 -> poly_term.coefficient,
								 iterator_p1 -> poly_term.degree + iterator_p2 -> poly_term.degree), P_result);
			iterator_p2 = iterator_p2 -> next;
		}
		iterator_p1 = iterator_p1 -> next;
	}
	node_ptr curr = P_result -> list -> next;
	node_ptr prev = P_result -> list;
	node_ptr removed_1 = 0, removed_2 = 0;
	// Add the terms with the same degree and remove from the list
 	 while (curr != 0) {
		if (prev && curr) {
			if (prev -> poly_term.degree == curr -> poly_term.degree) {
				add_term(create_node(prev -> poly_term.coefficient + curr -> poly_term.coefficient, prev -> poly_term.degree), P_result);
				removed_1 = prev;
				removed_2 = curr;
			}
		}
		prev = curr;
		curr = curr -> next;
    if (removed_1) remove_term(removed_1 -> poly_term.degree, P_result);
		if (removed_2) remove_term(removed_2 -> poly_term.degree, P_result);
	}
	return P_result;
}

void display_list(list *pl)
{
	node_ptr pt = pl -> list;
	while(pt) {
		printf("%dx^%d ", pt -> poly_term.coefficient, pt -> poly_term.degree);
		pt = pt -> next;
	}
	return;	
}

int main()
{
	list *p1 = create_list(p1);
	add_term(create_node(50, 1000), p1);
	add_term(create_node(3, 10), p1);
	add_term(create_node(34, 250), p1);
	add_term(create_node(1, 3), p1);
	add_term(create_node(-5, 4), p1);
	// 50 * x^1000 + 34 * x^250 + 3 * x^10 + -5 * x^4 + x^3 
	
	printf("P1(x) : ");
	display_list(p1);
	
	
	
	list *p2 = create_list(p2);
	add_term(create_node(7, 7000), p2);
  	add_term(create_node(13, 2000), p2);
  	add_term(create_node(2, 5), p2);
  	add_term(create_node(10, 4), p2);
  	add_term(create_node(150, 3), p2);
  	add_term(create_node(-12, 1), p2);
	// 7 * x^7000 + 13 * x^2000 +  2 * x^5 + 10 * x^4 + 150 * x^3 + -12 * x^1
	
	
	
	printf("\nP2(x) : ");
	display_list(p2);
	
	printf("\n\n");
	list *p_sum = create_list(p_sum);
	p_sum = add_poly(p1, p2, p_sum);
	printf("P1 + P2 : ");
	display_list(p_sum);
	// 7 * x^7000 13 * x^2000 50 * x^1000 34 * x^250 2 * x^5 5 * x^4 151 * x^3 -12 * x^1 
	
	printf("\n\n");
	
	list *p3 = create_list(p3);
	add_term(create_node(1, 1001), p3);
  	add_term(create_node(3, 20), p3);
  	// 1 * x^1001 3 * x^20 
  	
  	list *p4 = create_list(p4);
	add_term(create_node(1, 1), p4);
  	add_term(create_node(1, 25), p4);
  	// 1 * x^25 1 * x^1 
	
  	printf("P3(x) : ");
  	display_list(p3);
  
  	printf("\nP4(x) : ");
  	display_list(p4);
	
	list *p_mult = create_list(p_mult);
	p_mult = mult_poly(p3, p4, p_mult);
	printf("\nP3 * P4 = ");
	display_list(p_mult);

  // 1 * x^1026 1 * x^1002 3 * x^45 3 * x^21 
	
	
	
	return 0;
}
