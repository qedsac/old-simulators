/* arith.c */
void subtract(ADDR s);
/* control.c */
void stop(ADDR s);
void unused(ADDR s);
void test(ADDR s);
void jump(ADDR s);
void rjump(ADDR s);
/* cursor.c */
void show_cursor(void);
void erase_cursor(void);
void place_cursor(ADDR line,unsigned bit);
void move_cursor(int d_line,int d_bit);
void toggle_current_bit(void);
void display_current_bit(void);
/* display.c */
void display_bit(int tube,ADDR line,unsigned bit);
void display_line(int tube,ADDR line);
/* edit.c */
int edit(void);
void toggle_bit(ADDR line,unsigned bit);
/* exec_ins.c */
void exec_instruction(void);
/* execute.c */
void execute(void);
/* fetch.c */
void fetch_instruction(void);
/* graphics.c */
void set_up_graphics(void);
void clear_graphics(void);
void blob(int value,unsigned x,unsigned y);
void set_up_line(LINE value);
void show_line(unsigned x,unsigned y);
void draw_box(int visible,unsigned lo_x,unsigned lo_y,unsigned hi_x,unsigned hi_y);
/* init.c */
void initialize(void);
void clean_up(void);
void process_options(int argc,char *argv[]);
/* madm.c */
/* main.c */
int main(int argc,char *argv[]);
/* memory.c */
void load_negative(ADDR s);
void store_accumulator(ADDR s);
