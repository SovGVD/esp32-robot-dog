
/* -------------------- */

typedef void (*menuItemFunction)(int);

const typedef struct menuItem_t {
 char title[14];
 int funcArg;
 menuItemFunction func;
 int menuId;
 int menuParentId;
} menuItem;

typedef struct menuGroup_t {
  int startIndex;
  int menuLength;
  
} menuGroup;
