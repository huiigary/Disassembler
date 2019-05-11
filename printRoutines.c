#include <stdio.h>
#include <unistd.h>
#include "printRoutines.h"

/*
  You probably want to create a number of printing routines in this
  file.  Put the prototypes in printRoutines.h.
*/

int printPosition(FILE *out, unsigned long location) {

  return fprintf(out, ".pos 0x%lx\n", location);
}

/* This is a function to demonstrate how to do print formatting. It
 * takes the file descriptor the I/O is to be done to. You are not
 * required to use the same type of printf formatting, but you must
 * produce the same resulting format. You are also not required to
 * keep this function in your final result, and may replace it with
 * other equivalent instructions.
 *
 * The arguments for the format string in the example printing are
 * strictly for illustrating the spacing. You are free to construct
 * the output however you want.
 */

//--------------------------------------------------------------------------------------------------
 /// Given the register Number ---> gives String of the corresponding Register

 // GLOBAL VARIABLES
int ret=0;                 // the RETURN
char * register1;          //rA
char * register2;          //rB

char* stringCMove;       // cMovXX
char* stringCjump;       // jXX
char* stringOperation;   // OPq

 char* letter;     /// USE THIS WHEN rA,rB needs to be a letter :A B C D E F
 char* letter2;

char* r_Switch (int reg){   
    char* ret;
    switch(reg){
        case 0: ret="%rax"; 
        break;
        case 1: ret="%rcx";
        break;
        case 2:ret="%rdx";
        break;
        case 3:ret="%rbx";
        break;
        case 4:ret="%rsp";
        break;
        case 5:ret="%rbp";
        break;
        case 6:ret="%rsi";
        break;
        case 7:ret="%rdi";
        break;
        case 8:ret="%r8";
        break;
        case 9:ret="%r9";
        break;
        case 10:ret="%r10";
        break;
        case 11:ret="%r11";
        break;
        case 12:ret="%r12";
        break;
        case 13:ret="%r13";
        break;
        case 14:ret="%r14";
        break;
        case 15:ret="F"; // TODO
        break;
    }
    return ret;
}
char* operation_Switch (int reg){   
    char* ret;
    switch(reg){
        case 0: ret="addq"; 
        break;
        case 1: ret="subq";
        break;
        case 2:ret= "andq";
        break;
        case 3:ret="xorq";
        break;
        case 4:ret="mulq";
        break;
        case 5:ret="divq";
        break;
        case 6:ret="modq";
        break;
    }
    return ret;
}

char* printCondMove_Switch (int fn){   
    char* ret;
    switch(fn){
        case 1: ret="cmovle";
        break;
        case 2:ret="cmovl";
        break;
        case 3:ret="cmove";
        break;
        case 4:ret="cmovne";
        break;
        case 5:ret="cmovge";
        break;
        case 6:ret="cmovg";
    }
    return ret;
}
char* printCondJump_Switch (int fn){   
    char* ret;
    switch(fn){
        case 1: ret="jle";
        break;
        case 2:ret="jl";
        break;
        case 3:ret="je";
        break;
        case 4:ret="jne";
        break;
        case 5:ret="jge";
        break;
        case 6:ret="jg";
    }
    return ret;
}

char * letter_Switch(int reg){
        switch(reg){
                case 10: letter= "A";break;
                case 11: letter ="B";break;
                case 12: letter ="C";break;
                case 13: letter ="D";break;
                case 14: letter ="E";break;
                case 15: letter ="F";break;
            }
        return letter;
   }
           


/* 
 */
int printByte(FILE *out,  unsigned int code){
    char * halt ="halt";
    char * nop = "nop";
    char * ret = "ret";
      switch(code){
        case 0 :fprintf(out,"%-8s  #%-22d\n" ,halt, 00);
        case 1: fprintf(out,"%-8s  #%-22d\n", nop, 10);
        case 2: fprintf(out,"%-8s  #%-22d\n" ,ret, 90);
      }
      return 0;
  }
   
/* 
 */

char* pushq= "pushq";
char* popq= "popq";
char* rrmovq= "rrmovq";
int printTwoBytes(FILE *out, int code, int fn, int reg1, int reg2){ 
    switch(code){ 
    case 2:     //rrmovq rA, rB   --ex: 20AB  , 2012
      if( fn== 0){
          register1= r_Switch(reg1); // string of reg1 , includes rax, rbx ... r10 r11 r12 r13 r14, F
          register2= r_Switch(reg2); // string of reg2



               //if rA,rB are LETTERS:   20AB-------------------------
            if(reg2>= 10 && reg2 < 16 && reg1>=10 && reg1<16){ 
                 letter = letter_Switch(reg1);
                 letter2= letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%s%s\n",rrmovq, register1, register2          ,code,0,letter,letter2);
                  break;
            }
            if(reg2>= 10 && reg2 < 16){ 
                 letter = letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%d%s\n",rrmovq, register1, register2          ,code,0,reg1,letter);
                  break;
            }
            if(reg1>= 10 && reg1 < 16){ 
                 letter = letter_Switch(reg1);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%s%d\n",rrmovq, register1, register2          ,code,0,letter,reg2);
                  break;
            }
            if(reg1<=10 && reg2<=10){
                ret= fprintf(out, "%-8s %s, %s  #%d%d%d%d\n", rrmovq ,register1, register2,      code,fn,reg1,reg2);
                break;
            }
      }
        else {    // fn != 0  --- cmovqXX rA, rB         is one of : l, le, e , ne ,ge ,g
          stringCMove= ( printCondMove_Switch(fn) );  // prints: "cmovXX"
          register1= r_Switch(reg1);
          register2= r_Switch(reg2);

             //if rA,rB are LETTERS:   20AB-------------------------
            if(reg2>= 10 && reg2 < 16 && reg1>=10 && reg1<16){ 
                 letter = letter_Switch(reg1);
                 letter2= letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%s%s\n",stringCMove, register1, register2         ,code,0,letter,letter2);
                  break;
            }
            if(reg2>= 10 && reg2 < 16){ 
                 letter = letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%d%s\n",stringCMove, register1, register2         ,code,0,reg1,letter);
                  break;
            }
            if(reg1>= 10 && reg1 < 16){ 
                 letter = letter_Switch(reg1);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%s%d\n",stringCMove, register1, register2         ,code,0,letter,reg2);
                  break;
            }
            if(reg1<=10 && reg2<=10){
                ret= fprintf(out, "%-8s %s, %s  #%d%d%d%d\n", stringCMove ,register1, register2          ,code,fn,reg1,reg2);
                break;
            }
            else{
                 ret= fprintf(out, "%-8s %s, %s  #%d%d%d%d\n", stringCMove, register1, register2        ,code, fn, reg1, reg2);
                break;
            }
        }

    case 6: // OPQ rA, rB
        stringOperation= operation_Switch(fn);   //( AND , SUB, XOR ... etc) 
        register1= r_Switch(reg1);
        register2= r_Switch(reg2);

        
             //-------------------------
            if(reg2>= 10 && reg2 < 16 && reg1>=10 && reg1<16){ 
                 letter = letter_Switch(reg1);
                 letter2= letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%s%s\n",stringOperation, register1, register2         ,code,0,letter,letter2);
                  break;
            }
            if(reg2>= 10 && reg2 < 16){ 
                 letter = letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%d%s\n",stringOperation, register1, register2         ,code,0,reg1,letter);
                  break;
            }
            if(reg1>= 10 && reg1 < 16){ 
                 letter = letter_Switch(reg1);
                  ret= fprintf(out, "%-8s %s, %s  #%d%d%s%d\n",stringOperation, register1, register2         ,code,0,letter,reg2);
                  break;
            }
            if(reg1<=10 && reg2<=10){
                ret= fprintf(out, "%-8s %s, %s  #%d%d%d%d\n", stringOperation ,register1, register2          ,code,fn,reg1,reg2);
                break;
            }
            else{
                ret= fprintf(out, "%-8s %s, %s  #%d%d%d%d\n", stringOperation, register1, register2,    code, fn, reg1, reg2);
                break;

            }

        
    
    case 10: // A== pushQ
        register1= r_Switch(reg1);
        ret= fprintf (out, "%-8s %s  #%s%d%d%s\n", pushq, register1,     "A",fn, reg1, "F");
        break;
        
     case 11: //B == popQ
        register1= r_Switch(reg1);
        ret= fprintf (out, "%-8s %s  #%s%d%d%s\n",popq, register1   ,    "B",fn, reg1, "F");
     
    }
     return ret;
}
/* 
 */
int printNineBytes(FILE *out, int code, int fn, unsigned long long  val){ //unsigned long long val
    
    switch(code){
        case 7:
            if(fn==0){  // jmp DEST - 70
                ret= fprintf(out, "jmp 0x%llX  #%d%d%llu\n", val,       code, fn, val);
                 break;
            }
                else{  //jXX Dest  - 7fn
                    stringCjump= printCondJump_Switch(fn); // prints string "jXX"
                    ret= fprintf(out,"%s 0x%llX  #%d%d%llu\n",stringCjump, val          ,code,fn,val);
                    break;
                }
        case 8: // Call Dest
            ret= fprintf(out,"Call 0x%llX  #%d%d%llu\n", val              ,code,fn,val);
            break;
    }
    return ret;
}

/* 
 */
 char* irmovq= "irmovq";
 char* rmmovq= "rmmovq";
 char* mrmovq= "mrmovq";
int printTenBytes(FILE *out, int code, int reg1, int reg2, unsigned long long val){
    
    switch(code){
        case 3:                  //irmovq V rB  
         register2= r_Switch(reg2);   

//---------------------------------
        if(reg2>= 10 && reg2 < 16){ /// IF rB >= 10 --> convert into letter A B C D E F  /// REG2 WILL NEVER BE 15?
            letter = letter_Switch(reg2);
            ret = fprintf(out,"%-8s $%llu, %s  #%d%d%s%s$%llu\n", irmovq,val, register2         ,code,0,"F",letter,val);  // reg2= 15
            break;
        }
        else{  // rB is a NUMBER 0 -> 9
             ret = fprintf(out,"%-8s $%llu, %s  #%d%d%s%d$%llu\n", irmovq,val, register2         ,code,0,"F",reg2,val);  
            break;
        }

        case 4:                 // rmmovq rA D(rB)
            register1= r_Switch(reg1);
            register2= r_Switch(reg2);  


            // rA, rB  -- registers are LETTERS IN INSTRUCTION:   20AB
            if(reg2>= 10 && reg2 < 16 && reg1>=10 && reg1<16){ 
                 letter = letter_Switch(reg1);
                 letter2= letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, 0x%llu(%s)  #%d%d%s%s %llu\n",rmmovq, register1, val, register2          ,code,0,letter,letter2,val);
                  break;
            }
            if(reg2>= 10 && reg2 < 16){ 
                 letter = letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, 0x%llu(%s)  #%d%d%d%s %llu\n",rmmovq, register1, val, register2          ,code,0,reg1,letter,val);
                  break;
            }
            if(reg1>= 10 && reg1 < 16){ 
                 letter = letter_Switch(reg1);
                  ret= fprintf(out, "%-8s %s, 0x%llu(%s)  #%d%d%s%d %llu\n",rmmovq, register1, val, register2          ,code,0,letter,reg2,val);
                  break;
            }
        

            else{
                ret= fprintf(out, "%-8s %s, 0x%llu(%s)  #%d%d%d%d %llu\n",rmmovq, register1, val, register2             ,code,0,reg1,reg2,val);
                break;
            }
          
        case 5:                 // mrmovq D(rB) rA
            register1= r_Switch(reg1);
            register2= r_Switch(reg2);

                //if rA,rB are LETTERS:   20AB
            if(reg2>= 10 && reg2 < 16 && reg1>=10 && reg1<16){ 
                 letter = letter_Switch(reg1);
                 letter2= letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, 0x%llu(%s)  #%d%d%s%s %llu\n",rmmovq, register1, val, register2          ,code,0,letter,letter2,val);
                  break;
            }
            if(reg2>= 10 && reg2 < 16){ 
                 letter = letter_Switch(reg2);
                  ret= fprintf(out, "%-8s %s, 0x%llu(%s)  #%d%d%d%s %llu\n",rmmovq, register1, val, register2          ,code,0,reg1,letter,val);
                  break;
            }
            if(reg1>= 10 && reg1 < 16){ 
                 letter = letter_Switch(reg1);
                  ret= fprintf(out, "%-8s %s, 0x%llu(%s)  #%d%d%s%d %llu\n",rmmovq, register1, val, register2          ,code,0,letter,reg2,val);
                  break;
            }



            ret= fprintf(out, "%-8s 0x%llu(%s), %s  #%d%d%d%d %llu\n",mrmovq, val, register2, register1            ,code,0,reg1,reg2,val);
            break;
    }

    return 0;
}


int printPos(FILE *out,  unsigned int address ){
    //PRINTS .POS
    ret= fprintf(out, ".pos 0x%d", address);
    return ret;
}
int printPosSpace(FILE *out, unsigned int address){
    ret= fprintf(out, " .pos 0x%d", address); // NOTE THERE IS space before .pos
    return ret;
}

int printQuadValue (FILE *out, unsigned long long value){
    // prints the 
    ret= fprintf(out, ".quad 0x%llu", value);

    return ret;
}

int printByteValue (FILE *out, unsigned char value){
    // prints the .byte
    ret= fprintf(out, ".byte 0x%u", value);
    return ret;
}
  
