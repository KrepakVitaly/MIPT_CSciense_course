///  \brief
///
///  \description
///  \author		    Крепак zorroxied Виталий 016 ФРТК

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <assert.h>

//------------------------------------------------------------------------------
//------Constants---------------------------------------------------------------


//------------------------------------------------------------------------------
//------My_Types----------------------------------------------------------------

struct node_t
{
	node_t* left;
	node_t* right;
	node_t* parent;

	double      data;
	int   token_type;
};

struct tree_t
{
	node_t* root;
};

struct iter_t
{
	node_t* linked_tree;
	node_t* cur_node;
};

//------------------------------------------------------------------------------
//---------Functions_Prototypes-------------------------------------------------

void 	 Tree_Creation ( node_t* root );

void  	 Cut_Down_Tree ( tree_t* old_tree );

void	 Tree_Init	   ( iter_t* iterator );

void  	 Go_to_Left    ( iter_t* iterator );

void 	 Go_to_Right   ( iter_t* iterator );

void	 Go_to_Up	   ( iter_t* iterator );

node_t*  Grow_RBranch  ( int token_type, double data, iter_t* iterator );

node_t*  Grow_LBranch  ( int token_type, double data, iter_t* iterator );

node_t*  Grow_LBranch  ( int token_type, double data,
						 node_t* left, node_t* right );

void 	 Iter_Init	   ( iter_t* iterator );

node_t*  Create_Empty_Node   ();


void   CBinTree_PrePrint            (CNode* current);
void   CBinTree_InPrint             (CNode* current);
int    CBinTree_PostPrint           (CNode* current);

void   CBinTree_iterator_initialize (CBinTree_iterator* iter, CBinTree* tree);
void   CBinTree_iterator_initialize (CBinTree_iterator* iter, CBinTree* tree, CNode* el);



CNode* CNode_New                    ();
CNode* CNode_New                    (int type, double value,
                                     CNode* left, CNode* right);

void   CNode_PrintCurrent           (CNode* current);

void   CNode_Delete                 (CNode* current);

void   PutNumberInTree              (CNode* current, double* tempnumber);
CNode* FindInTree                   (CNode* current, double* tempnumber);
void   LoadTreePre                  (CBinTree* tree, FILE* input);


int    GetN                         (char* str, int* scount);
CNode* GlueNode                     (CNode* parrent, char* str);
void   GlobFileClose                (int i);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



