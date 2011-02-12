

/*
Luis Miguel Zavaleta Vazquez.
ITESM
MCC
A01330264
@LuisZavaleta



 */
#include <GL/glut.h>
#include <stdlib.h>

//Valores iniciales de los brazos, uno por cada grado de libertad
static int brazo00 = 10,brazo01,antebrazo00, antebrazo01, mano00, mano01;
static int dMedio0, dIndice0, dPulgar0, dAnular0, dMenique0;

static int brazo10 = -10,brazo11 = 180,antebrazo10, antebrazo11, mano10, mano11;
static int dMedio1, dIndice1, dPulgar1, dAnular1, dMenique1;


//struct que contiene todos los valores de un brazo,
struct ValoresBrazo {
	int brazo0;
	int brazo1;
	int antebrazo0;
	int antebrazo1;
	int mano0;
	int mano1;
	int dMedio;
	int dIndice;
	int dPulgar;
	int dAnular;
	int dMenique;
};


//metodo init
void init(void) 
{
	//Activamos el bufer de profundidad, que nos permite saber que pixel esta enfrente de otro para no repintarlo.
	glEnable (GL_DEPTH_TEST);	
	//ambiente.
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	//Posición de la cámara
	GLfloat position[] = { 0.0, 0.0, 10.0, 0.0 };	
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	//Activamos la iluminación	
	glEnable( GL_LIGHTING );
	//activamos la luz 0.
	glEnable( GL_LIGHT0 );
	
    glClearColor(0.5, 1.0, 1.0, 0.0);
}


/*
Este método sirve para pintar una esfera deformada, definir los grados de libertas y decidir la ubicación relativa.
radio:el radio de la esfera
scale: la escala scale[0] = x, scale[1] = y; scale[2] = z;
translatePosition: la traslación relativa translatePosition[0] = x,translatePosition[1]= y, translatePosition[2] = z
mov1: true si se mueve con respecto a z
mov2: true si se mueve con respecto a y
mov3: true si se mueve con respecto a x
shou: variable que indica la nueva posición con respecto a z
elbo: variable que indica la nueva posición con respecto a y
otr: variable que indica la nueva posición con respecto a x

*/

void pieza(float radio, float scale[], float translatePosition[],bool mov1, bool mov2, bool mov3, int shou, int elbo, int otr){	

	glTranslatef (translatePosition[0],translatePosition[1], translatePosition[2]);

	if(mov1){
		glRotatef ((GLfloat) shou, 0.0, 0.0, 1.0);
	}
	if(mov2){
		glRotatef ((GLfloat) elbo, 0.0, 1.0, 0.0);
	}
	if(mov3){	
		glRotatef ((GLfloat) otr, 1.0, 0.0, 0.0);
	}
	float moveOrigin = radio * scale[0];
	
	glTranslatef (moveOrigin, 0.0, 0.0);
	glPushMatrix();						
		 glScalef (scale[0], scale[1], scale[2]);	 	
		glutSolidSphere (radio,20,20);
	glPopMatrix(); 		
}


/*método para dibujar un brazo.
xTranslateRelative: pocición relativa del brazo con respecto a x.

ValoresBraz: variables usadas para menejar ese brazo.

*/
void brazo(float xTranslateRelative, struct ValoresBrazo valBrazo){

	//brazo uno
		glPushMatrix();
			float scale1[] = {3.0,1.0,1.0};
			float tp1[] ={xTranslateRelative,1.0,0.0};
			pieza(0.2,scale1,tp1,true,true,false,valBrazo.brazo0, valBrazo.brazo1, NULL);			
			float tp2[] ={0.6,0.0,0.0};	
			
			//antebrazo uno
			glPushMatrix();
				pieza(0.17,scale1,tp2,true,false,true,valBrazo.antebrazo0, NULL, valBrazo.antebrazo1);
				//mano uno 
				float tp3[] ={0.5,0.0,0.0};	
				float scale2[] = {2.0,1.0,1.0};
				pieza(0.1,scale2,tp3,true,true,false,valBrazo.mano0, valBrazo.mano1, NULL);	
		
				
				//dedo uno (medio)
				glPushMatrix();					
					float tp4[] ={.2,0.0,0.0};	
					float scale3[] = {5.5,0.2,1.0};
					pieza(0.02,scale3,tp4,false,true,false,NULL, valBrazo.dMedio, NULL);
				glPopMatrix();
				
				//dedo dos (indice)
				glPushMatrix();					
					float tp5[] ={.17,0.05,0.0};	
					//float scale3[] = {5.5,1.0,1.0};
					pieza(0.02,scale3,tp5,false,true,false,NULL, valBrazo.dIndice, NULL);
				glPopMatrix();
				
				//dedo tres (pulgar)
				glPushMatrix();				
					float tp6[] ={0.13,0.1,0.0};	
					float scale4[] = {5.0,1.2,1.0};
					pieza(0.02,scale4,tp6,false,true,false,NULL, valBrazo.dPulgar, NULL);
				glPopMatrix();
				
				//dedo cuatro (anular)
				glPushMatrix();				
					float tp7[] ={.17,-0.05,0.0};	
					//float scale3[] = {5.5,1.0,1.0};
					pieza(0.02,scale3,tp7,false,true,false,NULL, valBrazo.dAnular, NULL);
				glPopMatrix();
				
				//dedo cinco (meñique)
				glPushMatrix();				
					float tp8[] ={0.13,-0.1,0.0};	
					//float scale3[] = {5.5,1.0,1.0};
					pieza(0.02,scale3,tp8,false,true,false,NULL, valBrazo.dMenique , NULL);
				glPopMatrix();
			glPopMatrix();	
		glPopMatrix();
	
	}
	
	

void display(void)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat shininess[] = { 40.0 };
    
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 		
	glPushMatrix();	
   		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    	glMaterialfv(GL_FRONT, GL_SHININESS, shininess); 
	
		//Torso
		glPushMatrix();			
		 	glScalef (1.0, 3.0, 1.0);
			glutSolidSphere (.5,20,20);
		glPopMatrix(); 		

		//Cabeza		
		glPushMatrix();	
			glTranslatef (0.0,1.85, 0.0);					 
			glutSolidSphere (.4,10,10);
		glPopMatrix(); 			

		/*
		Mano izquierda:
		se controla con:
		brazo : 		q,Q,a,A
		antebrazo:		w,W,s,S
		mano:			e,E,d,D
		dedo medio:		1,2
		dedo indice:	3,4
		dedo pulgar:	5,6
		dedo anular:	7,8
		dedo meñique:	9,0
		*/
		
							


		struct ValoresBrazo valBra0;
		
		valBra0.brazo0 = brazo00;
		valBra0.brazo1 = brazo01;
		valBra0.antebrazo0 = antebrazo00;
		valBra0.antebrazo1 = antebrazo01;
		valBra0.mano0 = mano00;
		valBra0.mano1 = mano01;
		valBra0.dMedio = dMedio0;
		valBra0.dIndice = dIndice0;
		valBra0.dPulgar = dPulgar0;
		valBra0.dAnular = dAnular0;
		valBra0.dMenique  =dMenique0;
		
		brazo((float)0.4,valBra0);
		
						
		
		
			/*
		Mano izquierda:
		se controla con:
		brazo : 		t,T,g,G
		antebrazo:		y,Y,h,H
		mano:			u,U,j,J
		dedo medio:		z,Z
		dedo indice:	x,X
		dedo pulgar:	c,C
		dedo anular:	v,V
		dedo meñique:	b,B
		*/
		
		struct ValoresBrazo valBra1;
		
		valBra1.brazo0 = brazo10;
		valBra1.brazo1 = brazo11;
		valBra1.antebrazo0 = antebrazo10;
		valBra1.antebrazo1 = antebrazo11;
		valBra1.mano0 = mano10;
		valBra1.mano1 = mano11;
		valBra1.dMedio = dMedio1;
		valBra1.dIndice = dIndice1;
		valBra1.dPulgar = dPulgar1;
		valBra1.dAnular = dAnular1;
		valBra1.dMenique  =dMenique1;

		brazo((float)-0.4, valBra1);
		
		
		
	glPopMatrix(); 	
		

   
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (10, 10, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
	glOrtho (-6.0, 6.0, -3.0*((GLfloat)h*2)/(GLfloat)w, 
	   3.0*((GLfloat)h*2)/(GLfloat)w, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
}



/* ARGSUSED1 */
void keyboard (unsigned char key, int x, int y)
{
	/*
	
		static int brazo00,brazo01,antebrazo00, antebrazo01, mano00, mano01;
static int dMedio0, dIndice0, dPulgar0, dAnular0, dMenique0;

static int brazo10,brazo11,antebrazo10, antebrazo11, mano10, mano11;
static int dMedio1, dIndice1, dPulgar1, dAnular1, dMenique1;

	*/
  
   switch (key) {
      case 'q':
         brazo00 = (brazo00 + 5) % 360;        
         break;
      case 'Q':
         brazo00 = (brazo00 - 5) % 360;   
         break;
      case 'a':
         brazo01 = (brazo01 + 5) % 360;
         break;
      case 'A':
         brazo01 = (brazo01 - 5) % 360;
         break;         
         
         case 'w':
         antebrazo00 = (antebrazo00 + 5) % 360;        
         break;
      case 'W':
         antebrazo00 = (antebrazo00 - 5) % 360;   
         break;
         case 's':
         antebrazo01 = (antebrazo01 + 5) % 360; 
         break;
      case 'S':
         antebrazo01 = (antebrazo01 - 5) % 360;
         break;  
         
         
         
         case 'e':
         mano00 = (mano00 + 5) % 360;        
         break;
      case 'E':
         mano00 = (mano00 - 5) % 360;   
         break;
      case 'd':
         mano01 = (mano01 + 5) % 360;
         break;
      case 'D':
         mano01 = (mano01 - 5) % 360;
         break;
       
      case '1':
         dMedio0 = (dMedio0 + 5) % 360;
         break;
      case '2':
         dMedio0 = (dMedio0 - 5) % 360;
         break;

      case '3':
         dIndice0 = (dIndice0 + 5) % 360;
         break;
      case '4':
         dIndice0 = (dIndice0 - 5) % 360;
         break;

      case '5':
         dPulgar0 = (dPulgar0 + 5) % 360;
         break;
      case '6':
         dPulgar0 = (dPulgar0 - 5) % 360;
         break;

      case '7':
         dAnular0 = (dAnular0 + 5) % 360;
         break;
      case '8':
         dAnular0 = (dAnular0 - 5) % 360;
         break;
         
      case '9':
         dMenique0 = (dMenique0 + 5) % 360;
         break;
      case '0':
         dMenique0 = (dMenique0 - 5) % 360;
         break;  
         
         
         
         
         //Mano 2       
         
         case 't':
         brazo10 = (brazo10 + 5) % 360;        
         break;
      case 'T':
         brazo10 = (brazo10 - 5) % 360;   
         break;
      case 'g':
         brazo11 = (brazo11 + 5) % 360;
         break;
      case 'G':
         brazo11 = (brazo11 - 5) % 360;
         break;         
         
         case 'y':
         antebrazo10 = (antebrazo10 + 5) % 360;        
         break;
      case 'Y':
         antebrazo10 = (antebrazo10 - 5) % 360;   
         break;
         case 'h':
         antebrazo11 = (antebrazo11 + 5) % 360; 
         break;
      case 'H':
         antebrazo11 = (antebrazo11 - 5) % 360;
         break;  
         
         
         
         case 'u':
         mano10 = (mano10 + 5) % 360;        
         break;
      case 'U':
         mano10 = (mano10 - 5) % 360;   
         break;
      case 'j':
         mano11 = (mano11 + 5) % 360;
         break;
      case 'J':
         mano11 = (mano11 - 5) % 360;
         break;
       
      case 'z':
         dMedio1 = (dMedio1 + 5) % 360;
         break;
      case 'Z':
         dMedio1 = (dMedio1 - 5) % 360;
         break;

      case 'x':
         dIndice1 = (dIndice1 + 5) % 360;
         break;
      case 'X':
         dIndice1 = (dIndice1 - 5) % 360;
         break;

      case 'c':
         dPulgar1 = (dPulgar1 + 5) % 360;
         break;
      case 'C':
         dPulgar1 = (dPulgar1 - 5) % 360;
         break;

      case 'v':
         dAnular1 = (dAnular1 + 5) % 360;
         break;
      case 'V':
         dAnular1 = (dAnular1 - 5) % 360;
         break;
         
      case 'b':
         dMenique1 = (dMenique1 + 5) % 360;
         break;
      case 'B':
         dMenique1 = (dMenique1 - 5) % 360;
         break;  
         
      case 27:
         exit(0);
         break;
      default:
         break;
   }
   
            glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitWindowSize (1200, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
