#include<stdio.h>
#include <gtk/gtk.h>

typedef struct Calculator_childen
{ 
  GtkWidget *body;
  GtkWidget *display;
  GtkWidget *add_sign;
  GtkWidget *sub_sign;
  GtkWidget *mul_sign;
  GtkWidget *div_sign;
  GtkWidget *divR_sign;
  GtkWidget *equal_sign;
  GtkWidget *cancule_sign;
  GtkWidget *cancule_all_sign;
  GtkWidget *btw_1;
  GtkWidget *btw_2;
  GtkWidget *btw_3;
  GtkWidget *btw_4;
  GtkWidget *btw_5;
  GtkWidget *btw_6;
  GtkWidget *btw_7;
  GtkWidget *btw_8;
  GtkWidget *btw_9;  
  GtkWidget *btw_0;
   	
}Calculator_children; 

void *p_global_display;
char screen[20]={'\0'};
int lastScreenIndex=-1;
char c_sign='\0';
int c_screen_jumb= 0;
int leftHandAgument=0;
int rightHandAgument=0;
int isRightHandAgument=0;
int isResultGotten=0;
//
void close_and_log(){
     fprintf(stdout, "Calculator Closed! \n");
     gtk_main_quit();
 };
void close_window(GtkWidget *window){			  
   g_signal_connect(window, "destroy", G_CALLBACK(close_and_log), NULL);
};
//
GtkWidget * create_body(void){
    GtkWidget *box= gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    return box;    
};
//
 void handle_set_display(const gchar *label, int isJumb){
	 //
      if(isJumb && c_sign == '\0' ){
	c_sign= label[0];
	for(int i=0; i<20; i++){	
	   if(lastScreenIndex + 1 == i){
             screen[i]=' ';
	     screen[i + 1]=label[0];
	     screen[i + 2]=' ';
             lastScreenIndex= lastScreenIndex + 3;
	     c_screen_jumb=1;
             break;
           };	
	 };
	}else{
	  if(isJumb){
	   for(int i=0; i<20; i++){
             if(screen[i] == c_sign){
		screen[i]= label[0];
   		c_sign= label[0];		
	     };
	   };		   
	  }else{
	    for(int i=0; i<20; i++){		
              if(lastScreenIndex + 1 == i){
                screen[i]=label[0];
                lastScreenIndex= lastScreenIndex + 1;
                break;
              };
	    };
	  };
	};
 };
void handle_cancule_input(void){
     for(int i=0; i<20; i++){
       if(c_screen_jumb && isRightHandAgument && rightHandAgument == 0){
	  if(lastScreenIndex == i){
          screen[i]='\0';
	  screen[i - 1]='\0';
	  screen[i - 2]='\0';
          lastScreenIndex= lastScreenIndex -3;
	  c_screen_jumb=0;
	  isRightHandAgument=0;
	  c_sign='\0';
          };
	}else{
	   if(lastScreenIndex == i){
              screen[i]='\0';
              lastScreenIndex= lastScreenIndex -1;
	     //
	      if(isRightHandAgument){
                if(rightHandAgument > 0){
           	  rightHandAgument = rightHandAgument / 10;
                 };
    	       }else{
                 if(leftHandAgument > 0){
                  leftHandAgument = leftHandAgument / 10;
       	         };
     	      };
	   };
	   //
	};
      };

};
//
void reset_state(void){
    for(int i=0; i<20; i++){
       screen[i] = '\0';
     };
    lastScreenIndex=-1;
    c_sign='\0';
    c_screen_jumb= 0;
    leftHandAgument=0;
    rightHandAgument=0;
    isRightHandAgument=0;
    isResultGotten=0;
    gtk_button_set_label(p_global_display, "Empty");
}
//
void handle_equalTo(void){
    int result=0;	
    if(isRightHandAgument && rightHandAgument > 0){
       if(c_sign== '+'){
	  result = leftHandAgument + rightHandAgument;     
       }else if(c_sign== '-'){
          result = leftHandAgument - rightHandAgument;
       }else if(c_sign== '/'){
          result = leftHandAgument / rightHandAgument;
       }else if(c_sign== '%'){
          result = leftHandAgument % rightHandAgument;
       }else if(c_sign== '*'){
          result = leftHandAgument * rightHandAgument;
      };
     char displayResult[20]= {'\0'};
     char reversedResult[20]= {'\0'};
     int totalIndex=0;
     int resultRemovedLastValue= result;
     int lastValueOfResult= resultRemovedLastValue % 10;
     while (resultRemovedLastValue > 0){
	char stValue= lastValueOfResult + '0';
   	reversedResult[totalIndex]= stValue;
	totalIndex++;
	resultRemovedLastValue= resultRemovedLastValue / 10;        lastValueOfResult= resultRemovedLastValue % 10;	
     };
     totalIndex= totalIndex - 1;
     for(int i=totalIndex; i>=0; i--){
        displayResult[totalIndex - i]= reversedResult[i];
	//fprintf(stdout, "revased count dec- %d, inc %d, \n", i, (totalIndex - i));	
     };	
     for(int i=0; i<20; i++){
       screen[i] = '\0';	     
     }; 
     for(int i=0; i<totalIndex + 1; i++){
       screen[i] = displayResult[i];	     
     };
     isResultGotten= 1;
     //fprintf(stdout, "result reversed arr %s main arr %s \n", reversedResult, displayResult);  
    // fprintf(stdout, "result score %d la %d sign %c ra %d\n", result, leftHandAgument, c_sign, rightHandAgument);   
    };	    
};
//
void handle_btw_clicked(GtkButton *btw, gpointer user_data){
   int breakPoint=20;
   int bufferScreenContentCount=0;
   for(int i=0; i<breakPoint; i++){
     if(screen[i] != '\0') bufferScreenContentCount++;
     if((i + 1 == breakPoint) && (bufferScreenContentCount + 1 == breakPoint)) {reset_state(); reset_state();};
     
   };	   
   const gchar *label= gtk_button_get_label(btw);
   //fprintf(stdout, "button with label %s was  cliked \n", (label));
   if(isResultGotten) reset_state();
   if(label[0] == '+'){	   
     handle_set_display(label, 1);
     isRightHandAgument= 1;
   }else if(label[0] == '-'){	
     handle_set_display(label, 1);
     isRightHandAgument=1;
   }else if (label[0] == '*'){	   		   
     handle_set_display(label, 1);	   
     isRightHandAgument=1;	   
   }else if(label[0] == '/'){
     handle_set_display(label, 1);
     isRightHandAgument=1;
   }else if (label[0] == '%'){
     handle_set_display(label, 1);
     isRightHandAgument=1;
   }else if (label[0] == '='){
     handle_equalTo();	
   }else if (label[0] == 'C'){
     reset_state();	   
   }else if (label[0] == 'x'){		   
     handle_cancule_input();
   }else {
       handle_set_display(label, 0);	   
       if(isRightHandAgument){
      	       rightHandAgument = rightHandAgument * 10 + (label[0] - '0');
     	}else {
	leftHandAgument = leftHandAgument * 10 + (label[0] - '0');
	};
   };
   //fprintf(stdout, "left hand ag %d right hand ag %d \n", leftHandAgument, rightHandAgument);  
   gtk_button_set_label(p_global_display, screen);
};
 // 
GtkWidget * create_btw(char label[], char id[]){
   GtkWidget *btw= gtk_button_new_with_label(label);
   gtk_widget_set_size_request(btw, 70, 30);
   gtk_widget_set_name(btw, id);
   g_signal_connect(btw, "clicked", G_CALLBACK(handle_btw_clicked), NULL);
   return btw;
};
//   
int main(int argc, char *argv[])
{	
     fprintf(stdout, "Calculator Started! \n");	
     gtk_init(&argc, &argv); //this starts gtk fun flow 
    GtkWidget *window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    Calculator_children Content;
     //create body on heep;
    (Content.body) = create_body();
    //create calculator display
    (Content.display) = gtk_button_new_with_label("Empty");
    p_global_display= (Content.display);
    gtk_widget_set_name(Content.display, "c_d");
    gtk_widget_set_size_request(Content.display, -1, 20);
    //append display to body
    gtk_box_pack_start(GTK_BOX(Content.body), Content.display, FALSE, FALSE, 0);
    //create button
    (Content.add_sign) = create_btw("+", "add_s");
    (Content.sub_sign) = create_btw("-", "sub_s");
    (Content.mul_sign) = create_btw("*", "mul_s");
    (Content.div_sign) = create_btw("/", "div_s");
    (Content.divR_sign) = create_btw("%", "divR_s");
    (Content.equal_sign) = create_btw("=", "equal_s");
    (Content.cancule_sign) = create_btw("x", "x_s");
    (Content.cancule_all_sign) = create_btw("C", "c_s");
    (Content.btw_1) = create_btw("1", "b_1");
    (Content.btw_2) = create_btw("2", "b_2");
    (Content.btw_3) = create_btw("3", "b_3");
    (Content.btw_4) = create_btw("4", "b_4");
    (Content.btw_5) = create_btw("5", "b_5");
    (Content.btw_6) = create_btw("6", "b_6");
    (Content.btw_7) = create_btw("7", "b_7");
    (Content.btw_8) = create_btw("8", "b_8");
    (Content.btw_9) = create_btw("9", "b_9");
    (Content.btw_0) = create_btw("0", "b_0");
    //create layout
    GtkWidget *layout_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *layout_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *layout_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *layout_4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *layout_5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *layout_6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    //append buttons to layout
    //layout 1
     gtk_box_pack_start(GTK_BOX(layout_1), Content.add_sign, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_1), Content.sub_sign, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_1), Content.mul_sign, FALSE, FALSE, 0);
    //layout 2
     gtk_box_pack_start(GTK_BOX(layout_2), Content.div_sign, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_2), Content.divR_sign, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_2), Content.equal_sign, FALSE, FALSE, 0);
    //layout 3
     gtk_box_pack_start(GTK_BOX(layout_3), Content.btw_1, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_3), Content.btw_2, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_3), Content.btw_3, FALSE, FALSE, 0);
     //layout 4
     gtk_box_pack_start(GTK_BOX(layout_4), Content.btw_4, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_4), Content.btw_5, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_4), Content.btw_6, FALSE, FALSE, 0);
     //layout 5
     gtk_box_pack_start(GTK_BOX(layout_5), Content.btw_7, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_5), Content.btw_8, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_5), Content.btw_9, FALSE, FALSE, 0);
     //layout 6
     gtk_box_pack_start(GTK_BOX(layout_6), Content.cancule_all_sign, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_6), Content.btw_0, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(layout_6), Content.cancule_sign, FALSE, FALSE, 0);
    //append layout to body
    gtk_box_pack_start(GTK_BOX(Content.body), layout_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(Content.body), layout_2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(Content.body), layout_3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(Content.body), layout_4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(Content.body), layout_5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(Content.body), layout_6, FALSE, FALSE, 0);
   //fprintf(stdout, "%ld \n", sizeof(Calculator_children));  
    gtk_container_add(GTK_CONTAINER(window), Content.body);
    close_window(window);	
    gtk_widget_show_all(window);
    gtk_main();	
   //return 0;
}	

