#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <GL/glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double square_width,circle_radius,bubble_radius,x_spd,y_spd;
double max_speed,min_speed;

int pause_variable;

struct point
{
	double x,y,z;
};

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

struct point position_vectors[5],speed_vectors[5];

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

bool check(int i,double d)
{


    double v=sqrt(pow(abs(speed_vectors[i].x),2)+pow(abs(speed_vectors[i].y),2));

    if((d>1 && v<max_speed)|| (d<1 && v>min_speed)) return true;

    return false;


}

bool checkInCircle(int i)
{

    double distance_between_centres=sqrt(pow(position_vectors[i].x,2)+pow(position_vectors[i].y,2));
    if(distance_between_centres<=circle_radius-bubble_radius)
    {
      //  printf("%0.02f\n",distance_between_centres);
       return true;
    }

    return false;


}

void increase_speed(double d)
{

   for(int i=0;i<5;i++)
   {

      if(check(i,d)){
       speed_vectors[i].x*=d;
       speed_vectors[i].y*=d;
      }


   }


}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glColor3f(0, 1.0, 0);
		glBegin(GL_LINES);{
			glVertex3f( a,a,0);
			glVertex3f(a,-a,0);

			glVertex3f(-a,-a,0);
			glVertex3f(-a, a,0);

			glVertex3f(-a,-a, 0);
			glVertex3f(a,-a,0);

			glVertex3f( -a,a,0);
			glVertex3f(a,a,0);
		}glEnd();
}




void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];

    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawBubbles()
{

 glColor3f(0.4,0.4,0);


    glPushMatrix();
    {
     glTranslatef(position_vectors[0].x,position_vectors[0].y,0);
     drawCircle(bubble_radius,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
       glTranslatef(position_vectors[1].x,position_vectors[1].y,0);
       drawCircle(bubble_radius,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(position_vectors[2].x,position_vectors[2].y,0);
        drawCircle(bubble_radius,20);
    }
    glPopMatrix();

      glPushMatrix();
    {
       glTranslatef(position_vectors[3].x,position_vectors[3].y,0);
       drawCircle(bubble_radius,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(position_vectors[4].x,position_vectors[4].y,0);
        drawCircle(bubble_radius,20);
    }
    glPopMatrix();





}


void drawSS()
{

    glPushMatrix();
    {
      glColor3f(0,1,0);
      drawSquare(square_width);
    }
    glPopMatrix();

     glPushMatrix();
    {
      glColor3f(1,0,0);
     drawCircle(circle_radius,30);
    }
    glPopMatrix();

    drawBubbles();




}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;
		case 'p':
		    if(pause_variable) pause_variable=0;
		    else pause_variable=1;
            break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
			increase_speed(0.5);
			break;
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			increase_speed(1.1);
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				//drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


double dotGun(struct point A, struct point B)
{

    double product = 0;
    product = product + (A.x*B.x)+(A.y*B.y)+(A.z*B.z);
    return product;
}


void collide_with_circle(int i)
{

    if(dotGun(position_vectors[i],speed_vectors[i])<0)
    {

        return;
    }

    printf("inside\n");

    double hor_proj_x=-((dotGun(speed_vectors[i],position_vectors[i])/(pow(position_vectors[i].x,2)+pow(position_vectors[i].y,2)))*position_vectors[i].x);
    double hor_proj_y=-((dotGun(speed_vectors[i],position_vectors[i])/(pow(position_vectors[i].x,2)+pow(position_vectors[i].y,2)))*position_vectors[i].y);
    double ver_proj_x=(dotGun(speed_vectors[i],position_vectors[i])/(pow(position_vectors[i].x,2)+pow(position_vectors[i].y,2)))*position_vectors[i].y;
    double ver_proj_y=(dotGun(speed_vectors[i],position_vectors[i])/(pow(position_vectors[i].x,2)+pow(position_vectors[i].y,2)))*(-position_vectors[i].x);

    speed_vectors[i].x=hor_proj_x+ver_proj_x;
    speed_vectors[i].y=hor_proj_y+ver_proj_y;


}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();


	gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

    //glColor3f(1,0,0);
    //drawSquare(10);

    drawSS();






	glutSwapBuffers();
}


void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera

	for(int i=0;i<5;i++)
    {


        // circle collision

        if(checkInCircle(i))
        {
          //  printf("in circle\n");
           double distance_between_centres=sqrt(pow(position_vectors[i].x,2)+pow(position_vectors[i].y,2));
           if(distance_between_centres>=64.8)
           {

              collide_with_circle(i);

             // printf("yes\n");
           }


        }

        else
        {
             if(abs(position_vectors[i].x)+bubble_radius>square_width)
         {
            speed_vectors[i].x*=(-1.0);

         }
         if(abs(position_vectors[i].y)+bubble_radius>square_width)
         {
            speed_vectors[i].y*=(-1.0);

         }

        }

        if(pause_variable==0){
        position_vectors[i].x+=speed_vectors[i].x;
        position_vectors[i].y+=speed_vectors[i].y;
        }

    }



	glutPostRedisplay();
}



void init(){
	//codes for initialization
	drawgrid=0;
	//drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	square_width=150;
	circle_radius=80;
	bubble_radius=15;
	x_spd=0.008;
	y_spd=0.008;
	max_speed=0.2;
	min_speed=0.02;
	pause_variable=0;

	for(int i=0;i<5;i++)
    {

        position_vectors[i].x=-square_width+bubble_radius;
        position_vectors[i].y=-square_width+bubble_radius;
        position_vectors[i].z=0;

        //speed vector x =x_spd
        //speed_vectr y=y _spd

         speed_vectors[i].x=cos(angle)*x_spd - sin(angle)*y_spd;
         speed_vectors[i].y=sin(angle)*x_spd + cos(angle)*y_spd;
         speed_vectors[i].z=0;
         angle+=5;


    }

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
