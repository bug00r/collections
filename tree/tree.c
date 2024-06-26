#include "tree.h"

struct tree_node_data_vtbl {
	struct data_vtbl super;
	void (* print_children)(TreeNodeData *data);
};

static void tree_node_data_free_(Data * data) {
	TreeNodeData * const _data = (TreeNodeData *)data;
	printf("//TODO recursive delete of TreeNode* data and children");
}

static size_t tree_node_data_real_size_(Data * data) {
	TreeNodeData * const _data = (TreeNodeData *)data;
	size_t size = sizeof(TreeNodeData);
	if (_data)
		size += _data->super.size;
	return size;
}

static void tree_node_data_print_children_(TreeNodeData *data) {
	printf("CALL: _tree_node_data_print_children_(TreeNodeData *data)");
}

static Data * tree_node_data_copy_(Data * _data) {
	return NULL;
}
static bool tree_node_data_equals_(Data * _data, Data *_data2) {
	return false;
}
static void tree_node_data_print_(Data *data) {
	printf("//TODO tree_node_data_print_(Data *data)");
}

TreeNodeData * tree_node_data_new_empty() {
	static struct tree_node_data_vtbl const tndctbl = {
		{&tree_node_data_free_,
		&tree_node_data_copy_,
		&tree_node_data_equals_,
		&tree_node_data_real_size_,
		&tree_node_data_print_},
		&tree_node_data_print_children_
	};
	TreeNodeData * newdata = malloc(sizeof(TreeNodeData));
	data_ctor(&newdata->super);
	newdata->super.vptr = (struct data_vtbl*)&tndctbl;
	return newdata;
}
TreeNodeData * tree_node_data_new() {
	return tree_node_data_new_empty();
}
void tree_node_data_new_dest(TreeNodeData **dest) {
	*dest = tree_node_data_new();
}

#if 0
//test late binding method call.
#endif
void tree_node_print_children(TreeNodeData * const _data) {
	TreeNodeData * const data = _data;
	(*data->vptr->print_children)(data);
}

void tree_node_data_free(TreeNodeData * _data) {
	TreeNodeData * data = _data;
	data_free((Data *)data);
}


#if 0
/**
	creates new empty node
*/
#endif
TreeNode * tree_node_new() { 
	TreeNode * newnode = malloc(sizeof(TreeNode));
	newnode->data = NULL;
	newnode->parent = NULL;
	newnode->children = llist_new();
	return newnode; 
}
#if 0
/**
	creates new empty node and add to dest.
*/
#endif
void tree_node_new_dest(TreeNode ** dest) { 
	*dest = tree_node_new();
}

static void _free_all_childs_(LList * _childs) {
	LList * childs = _childs;
	if (childs != NULL && childs->start != NULL) {
		LlNode * curnode = childs->start;
		LlNode * tmp = NULL;
		while( curnode != NULL) {
			tmp = curnode->next;
			#if 0
				//current child tree node
			#endif
			Data * ndata = ll_node_detach_data(curnode);
			tree_node_free((TreeNode **)&ndata->data);
			data_free(ndata);
			curnode = tmp;
		}
	}
}

#if 0
/**
	deletes node. It will deletes data too
*/
#endif
void tree_node_free(TreeNode **_node) { 
	TreeNode * node = *_node;
	if ( node != NULL ) {
		//free all children data which are tree_nodes too
		_free_all_childs_(node->children);
		llist_free(&node->children);
		Data * data = tree_node_detach_data(node);
		data_free(data);
		free(node);
		*_node = NULL;
	}
}
#if 0
/**
	deletes nodes content. It will deletes data too
*/
#endif
void tree_node_clear(TreeNode *_node) { 
	TreeNode * node = _node;
	Data * data = node->data;
	data_free(data);
	node->data = NULL;
	node->parent = NULL;
	_free_all_childs_(node->children);
	llist_clear(node->children);
}
#if 0
/**
	attach new data to node. Does nothing if data exist.
*/
#endif
void tree_node_attach_data(TreeNode *_node, Data * _data) { 
	TreeNode * node = _node;
	if(node->data == NULL) {
		node->data = _data;
	}
}
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one returned.
*/
#endif
Data * tree_node_attach_data_override(TreeNode *_node, Data * _data) { 
	TreeNode * node = _node;
	Data * olddata = node->data;
	node->data = _data;
	return olddata;
}
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one will
	linked to dest pointer.
*/
#endif
void tree_node_attach_data_override_dest(Data **dest, TreeNode *node, Data * data) { 
	*dest = tree_node_attach_data_override(node, data);
}
#if 0
/**
	create copy of tree node.
*/
#endif
TreeNode * tree_node_copy(TreeNode * src) { 
	TreeNode * copy = NULL;
	if ( src != NULL ){
		copy = tree_node_new();
		copy->data = data_copy(src->data);
		copy->parent = src->parent;
		LList * childs = src->children;
		if (childs != NULL) {
			LlNode * curnode = childs->start;
			LlNode * tmp = NULL;
			while( curnode != NULL) {
				tmp = curnode->next;
				#if 0
					//current child tree node
				#endif
				TreeNode * cctn = (TreeNode *)curnode->data->data;
				TreeNode * cctn_cpy = tree_node_copy(cctn);
				cctn_cpy->parent = NULL;
				//append copy to children list.
				tree_node_append_child(copy, &cctn_cpy);
				curnode = tmp;
			}
		}
	}
	return copy;
}
#if 0
/**
	Copy node src and saves result to dest.
*/
#endif
void tree_node_copy_dest(TreeNode ** dest, TreeNode * src) { 
	*dest = tree_node_copy(src);
}
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
Data * tree_node_detach_data(TreeNode * _node) { 
	Data * data = NULL;
	TreeNode * node = _node;
	if (node != NULL) {
		data = node->data;
		node->data = NULL;
	}
	return data;
}
#if 0
/**
	removes data from node and add the removed data to dest. If no data attached NULL will added.
*/
#endif
void tree_node_detach_data_dest(Data ** dest, TreeNode *node) { 
	*dest = tree_node_detach_data(node);
}

//static Data * _child_node_data_new_(void **data, size_t size) {
//
//	Data * newdata = malloc(sizeof(Data));
//	static struct data_vtbl const vtbl = {
//		&_data_free_,
//		&_data_copy_,
//		&_data_equals_,
//		&_data_real_size_,
//		&_data_print_
//	};
//}

LlNode * _create_llist_entry_from_node_(TreeNode ** node) {
	LlNode * childentry = ll_node_new();
	Data * data = data_new((void**)node, sizeof(TreeNode));
	ll_node_attach_data(childentry, data);
	return childentry;
}

#if 0
/**
	Append Child at the end of child nodes. If child is new its new parent is parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_append_child(TreeNode * _parent, TreeNode ** _newchild) {
	TreeNode * parent = _parent;
	TreeNode * newchild = *_newchild;
	*_newchild = NULL;
	if ( newchild != NULL && parent != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		newchild->parent = parent;
		llist_append_node(parent->children, _create_llist_entry_from_node_(&newchild));
	}
}
#if 0
/**
	Append Child at beginning of child nodes. If child is new its new parent is parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_prepend_child(TreeNode * _parent, TreeNode * _newchild) {
	TreeNode * parent = _parent;
	TreeNode * newchild = _newchild;
	if ( newchild != NULL && parent != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		newchild->parent = parent;
		llist_prepend_node(parent->children, _create_llist_entry_from_node_(&newchild));
	}
}

static bool _search_tree_node_equal_ref_(void * nodedata, void * searchdata) {
	return nodedata == searchdata;
}

#if 0
/**
	Insert Child before sibling. If child is new its new parent is siblings parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_insert_before_child(TreeNode * _sibling, TreeNode * _newchild) {
	TreeNode * sibling = _sibling;
	TreeNode * newchild = _newchild;
	if ( newchild != NULL && sibling != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		TreeNode * parent = sibling->parent;
		newchild->parent = parent;
		LlNode * found = llist_search_node_first(parent->children, sibling,_search_tree_node_equal_ref_);
		if (found != NULL ) {
			llist_insert_before(parent->children, found, _create_llist_entry_from_node_(&newchild));
		}
	}
}
#if 0
/**
	Insert Child after sibling. If child is new its new parent is siblings parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_insert_after_child(TreeNode * _sibling, TreeNode * _newchild) {
	TreeNode * sibling = _sibling;
	TreeNode * newchild = _newchild;
	if ( newchild != NULL && sibling != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		TreeNode * parent = sibling->parent;
		if (parent != NULL) {
			newchild->parent = parent;
			LlNode * found = llist_search_node_first(parent->children, sibling,_search_tree_node_equal_ref_);
			if (found != NULL ) {
				llist_insert_after(parent->children, found, _create_llist_entry_from_node_(&newchild));
			}
		}
	}
}
#if 0
/**
	Deletes child. If child is valid child of parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child(TreeNode * _parent, TreeNode * _deletechild) {
	TreeNode * parent = _parent;
	TreeNode * deletechild = _deletechild;
	if ( deletechild != NULL && parent != NULL /* && newchild->treeref == parent->treeref */) {
		LlNode * found = llist_search_node_first(parent->children, deletechild, _search_tree_node_equal_ref_);
		if (found != NULL && deletechild == found->data->data ) {
			tree_node_free(&deletechild);
			llist_delete_node(parent->children, found);
		}
	}
}
#if 0
/**
	Deletes node before sibling. If child is valid child of siblings parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child_before(TreeNode * _sibling, TreeNode * _deletechild) {
	TreeNode * sibling = _sibling;
	TreeNode * deletechild = _deletechild;
	if ( deletechild != NULL && sibling != NULL /* && newchild->treeref == parent->treeref */) {
		TreeNode * parent = sibling->parent;
		if (parent != NULL) {
			//CURRENTLY create llist_search_node_previous
			LlNode * found = llist_search_previous_node(parent->children, deletechild, _search_tree_node_equal_ref_);
			if (found != NULL && deletechild == found->data->data ) {
				tree_node_free(&deletechild);
				llist_delete_node(parent->children, found);
			}
		}
	}
}
#if 0
/**
	Deletes node after sibling. If child is valid child of siblings parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child_after(TreeNode * _sibling, TreeNode * _deletechild) {
	TreeNode * sibling = _sibling;
	TreeNode * deletechild = _deletechild;
	if ( deletechild != NULL && sibling != NULL /* && newchild->treeref == parent->treeref */) {
		TreeNode * parent = sibling->parent;
		if (parent != NULL) {
			LlNode * found = llist_search_node_first(parent->children, deletechild, _search_tree_node_equal_ref_);
			if (found != NULL && found->next != NULL && found->next->data != NULL) {
				LlNode * next = found->next;
				TreeNode * treedata = (TreeNode *)found->next->data->data;
				tree_node_free(&treedata);
				llist_delete_node(parent->children, next);
			}
		}
	}
}

Tree * tree_new(TreeNode * root) {
	size_t tree_size = sizeof(Tree);
	Tree * newtree = malloc(tree_size);
	Tree base = {newtree, root};
	memcpy(newtree, &base, tree_size);
	return newtree;
}

void tree_free(Tree * tree) {
	tree_node_free(&tree->root);
	free(tree);
}