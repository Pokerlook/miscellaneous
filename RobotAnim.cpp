#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>

#include <gl/glut.h>
#include <GL/glui.h>

static int right_shoulder = 0, right_elbow = 0; // 오른팔
static int left_shoulder = 0, left_elbow = 0;   // 왼팔
static int right_joint = 0, right_knee = 0; // 오른 다리
static int left_joint = 0, left_knee = 0; // 왼 다리

static int isWireModel = true;

GLint mouseX = 0; // <- 추가할 부분
GLint mouseY = 0; // <- 추가할 부분
GLint mouseState = 0; // <- 추가할 부분
GLint mouseButton = 0; // <- 추가할 부분
GLfloat xTheta = 0.0, yTheta = 0.0; // <- 추가할 부분
GLfloat scale = 1.0, scaleDelta = 1.01; // <- 추가할 부분

//// add 
GLUI* glui;
GLUI_EditText* edittext;
GLUI_RadioGroup* radio;

int main_window;
std::string text = "60172207 Choi Dongil";
float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float obj_pos[] = { 0.0, 0.0, 0.0 };


int select_color = 0; // 0123 ua, la, ul, ll

float color_upperArm[3] = { 1, 0, 0 };
float color_lowerArm[3] = { 0, 1, 0 };
float color_upperLeg[3] = { 0, 0, 1 };
float color_lowerLeg[3] = { 1, 0, 1 };

const char* string_list[] = { "Black", "White", "Red", "Green", "Blue" };
int   clear_color = 0;

float scrollRGB[3] = { 0,0,0 };

struct animInfo
{
    int right_upeer_arm = 0;
    int right_lower_arm = 0;
    int right_upper_leg = 0;
    int right_lower_leg= 0;

    int left_upper_arm = 0;
    int left_lower_arm = 0;
    int left_upper_leg = 0;
    int left_lower_leg = 0;
};

std::vector<animInfo> anim_array(100);

bool isAnimateNow = false;

int current_anim_Index = 0;

void AnimTImer(int Value);

void RightArm() {

    glPushMatrix();
    glTranslatef(0.75, 1, 0.0);     // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)right_shoulder, 1.0, 0, 0.0);
    glTranslatef(-0.75, -1, 0.0);     // Pivot으로 지정할 위치를 원점으로 이동

    glPushMatrix();
    glTranslatef(0.75f, 1.f, 0.0f); // (1, 1, 0)으로 이동

    glPushMatrix();

    glColor3fv(color_upperArm);

    GLUquadricObj* cylinder = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(-90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    glScaled(1, 1, 1.0); // 지름 조절
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder, GLU_FILL);
    }
    gluCylinder(cylinder, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder);


    glTranslatef(0, -1, 0.0); // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)right_elbow, 1, 0, 0.0); // 원점을 기준으로 회전
    glTranslatef(0, 1, 0.0); // Pivot으로 지정할 위치를 원점으로 이동

    glPushMatrix();
    glColor3fv(color_lowerArm);
    GLUquadricObj* cylinder2 = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder2, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder2, GLU_FILL);
    }
    gluCylinder(cylinder2, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder2);


    glPopMatrix();
    glPopMatrix();
}

void LeftArm() {

    glPushMatrix();
    glTranslatef(-0.75, 1, 0.0);     // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)left_shoulder, 1.0, 0, 0.0);
    glTranslatef(0.75, -1, 0.0);     // Pivot으로 지정할 위치를 원점으로 이동

    glPushMatrix();
    glTranslatef(-0.75f, 1.f, 0.0f); // (1, 1, 0)으로 이동

    // 숄더 그리기
    glPushMatrix();
    glColor3fv(color_upperArm);
    GLUquadricObj* cylinder = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(-90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder, GLU_FILL);
    }
    gluCylinder(cylinder, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder);


    glTranslatef(0, -1, 0.0); // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)left_elbow, 1, 0, 0.0); // 원점을 기준으로 회전
    glTranslatef(0, 1, 0.0); // Pivot으로 지정할 위치를 원점으로 이동

    //엘보 그리기
    glPushMatrix();
    glColor3fv(color_lowerArm);
    GLUquadricObj* cylinder2 = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder2, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder2, GLU_FILL);
    }
    gluCylinder(cylinder2, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder2);


    glPopMatrix();
    glPopMatrix();
}

void RightLeg() {
    glPushMatrix();
    glTranslatef(0.4, -1, 0.0);     // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)right_joint, 1.0, 0, 0.0);
    glTranslatef(-0.4, 1, 0.0);     // Pivot으로 지정할 위치를 원점으로 이동

    glPushMatrix();
    glTranslatef(0.4f, -1.f, 0.0f); // (1, 1, 0)으로 이동

    // 고관절 그리기
    glPushMatrix();
    glColor3fv(color_upperLeg);
    GLUquadricObj* cylinder = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(-90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder, GLU_FILL);
    }
    gluCylinder(cylinder, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder);

    glTranslatef(0, -1, 0.0); // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)right_knee, 1, 0, 0.0); // 원점을 기준으로 회전
    glTranslatef(0, 1, 0.0); // Pivot으로 지정할 위치를 원점으로 이동

    //무릎 그리기
    glPushMatrix();
    glColor3fv(color_lowerLeg);
    GLUquadricObj* cylinder2 = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder2, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder2, GLU_FILL);
    }
    gluCylinder(cylinder2, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder2);

    glPopMatrix();
    glPopMatrix();
}

void LeftLeg() {

    glPushMatrix();
    glTranslatef(-0.4, -1, 0.0);     // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)left_joint, 1.0, 0, 0.0);
    glTranslatef(0.4, 1, 0.0);     // Pivot으로 지정할 위치를 원점으로 이동

    glPushMatrix();
    glTranslatef(-0.4f, -1.f, 0.0f); // (1, 1, 0)으로 이동

    // 고관절 그리기
    glPushMatrix();
    glColor3fv(color_upperLeg);
    GLUquadricObj* cylinder = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(-90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder, GLU_FILL);
    }
    gluCylinder(cylinder, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder);


    glTranslatef(0, -1, 0.0); // Pivot 지정 및 객체 이동
    glRotatef((GLfloat)left_knee, 1, 0, 0.0); // 원점을 기준으로 회전
    glTranslatef(0, 1, 0.0); // Pivot으로 지정할 위치를 원점으로 이동

    //무릎 그리기
    glPushMatrix();
    glColor3fv(color_lowerLeg);
    GLUquadricObj* cylinder2 = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder2, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder2, GLU_FILL);
    }
    gluCylinder(cylinder2, 0.2, 0.2, 1, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(cylinder2);


    glPopMatrix();
    glPopMatrix();
}

void display(void) {

    switch (clear_color)
    {
    case 0:    // black
        glClearColor(0, 0, 0, 1.0f);
        break;

    case 1:    // white
        glClearColor(1, 1, 1, 1.0f);
        break;

    case 2:    // red
        glClearColor(1, 0, 0, 1.0f);
        break;

    case 3:    // green
        glClearColor(0, 1, 0, 1.0f);
        break;

    case 4:    // blue
        glClearColor(0, 0, 1, 1.0f);
        break;

    default:
        glClearColor(0, 0, 0, 1.0f);
        break;
    }


    glShadeModel(GL_SMOOTH);

    GLfloat light1Pos[] = { -15, -15, 15, 1 };
    GLfloat grayColor[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);

    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grayColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
    glEnable(GL_LIGHT0);

    glPopMatrix();

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f, // 카메라 위치 (x, y, z)
        0.0f, 0.0f, 0.0f, // 카메라를 바라보는 지점 (x, y, z)
        0.0f, 1.0f, 0.0f); // 카메라의 위쪽 방향 (x, y, z)

    glPushMatrix();
    glColor3f(1.f, 1.f, 1.f); // 텍스트 색상 설정
    glRasterPos2i(-5, -5); // 텍스트 위치 설정
    for (unsigned int i = 0; i < text.length(); ++i)    // 텍스트 그리기
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    glPopMatrix();

    glRotatef(xTheta, 1.0, 0.0, 0.0);
    glRotatef(yTheta, 0.0, 1.0, 0.0);
    glTranslatef(obj_pos[0], obj_pos[1], -obj_pos[2]);
    glMultMatrixf(view_rotate);

    glScalef(scale, scale, scale);


    // 몸통
    glPushMatrix();
    glColor3f(1, 1, 0); // yello
    GLUquadricObj* cylinder = gluNewQuadric();
    glTranslatef(0, -1, 0);
    glRotated(-90, 1, 0, 0); // 실린더를 세로로 그리기 위해 회전
    glScaled(1, 1, 1.0); // 지름 조절
    if (isWireModel)
    {
        gluQuadricDrawStyle(cylinder, GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(cylinder, GLU_FILL);
    }
    gluCylinder(cylinder, 0.5, 0.5, 2, 20, 20);
    glPopMatrix();
    gluDeleteQuadric(cylinder);

    // 머리
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glColor3f(1, 1, 0); // yello
    glScaled(1.0, 1, 1);
    if (isWireModel)
    {
        glutWireSphere(0.5, 15, 15);
    }
    else
    {
        glutSolidSphere(0.5, 15, 15);
    }
    glPopMatrix();


    RightArm();
    LeftArm();
    RightLeg();
    LeftLeg();


    glutSwapBuffers();

}

void myMouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseState = state;
        mouseButton = btn;
        mouseX = x;
        mouseY = y;
    }
    else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        mouseState = state;
        mouseButton = btn;
        mouseX = x;
        mouseY = y;
    }
    else if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        xTheta = yTheta = 0.0;
        scale = 1.0;
    }
    else return;

    glutPostRedisplay();
}

void myMotion(int x, int y)
{
    if (mouseButton == GLUT_LEFT_BUTTON) {
        yTheta -= (GLfloat)(mouseX - x);
        xTheta -= (GLfloat)(mouseY - y);
    }

    else if (mouseButton == GLUT_RIGHT_BUTTON) {
        if (mouseY != y)
            scale = scale * pow((double)scaleDelta, (double)(mouseY - y));
    }
    else return;

    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        isWireModel = false;
        break;
    case 'W':
        isWireModel = true;
        break;

    case 'f':
        left_shoulder = (left_shoulder - 5) % 360;
        break;
    case 'v':
        left_shoulder = (left_shoulder + 5) % 360;
        break;
    case 'd':
        left_elbow = (left_elbow - 5) % 360;
        break;
    case 'c':
        left_elbow = (left_elbow + 5) % 360;
        break;

    case 'j':
        right_shoulder = (right_shoulder - 5) % 360;
        break;
    case 'n':
        right_shoulder = (right_shoulder + 5) % 360;
        break;
    case 'k':
        right_elbow = (right_elbow - 5) % 360;
        break;
    case 'm':
        right_elbow = (right_elbow + 5) % 360;
        break;

    case 's':
        left_joint = (left_joint - 5) % 360;
        break;
    case 'x':
        left_joint = (left_joint + 5) % 360;
        break;
    case 'a':
        left_knee = (left_knee - 5) % 360;
        break;
    case 'z':
        left_knee = (left_knee + 5) % 360;
        break;

    case 'l':
        right_joint = (right_joint - 5) % 360;
        break;
    case ',':
        right_joint = (right_joint + 5) % 360;
        break;
    case ';':
        right_knee = (right_knee - 5) % 360;
        break;
    case '.':
        right_knee = (right_knee + 5) % 360;
        break;

    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/***************************************** myGlutIdle() ***********/

void myGlutIdle(void)
{
    /* According to the GLUT specification, the current window is
       undefined during an idle callback.  So we need to explicitly change
       it if necessary */
    if (glutGetWindow() != main_window)
        glutSetWindow(main_window);


    glutPostRedisplay();
    GLUI_Master.sync_live_all();
}

void color_cb(int control)
{
    // 커스텀컬러 라디오버튼. 0123 ua, la, ul, ll
    if (control == 1)
    {
        switch (radio->get_int_val())
        {
        case 0:    // upper arm
            printf_s("upper arm 라디오 버튼 클릭");
            scrollRGB[0] = color_upperArm[0];
            scrollRGB[1] = color_upperArm[1];
            scrollRGB[2] = color_upperArm[2];
            break;

        case 1:     // lower arm
            scrollRGB[0] = color_lowerArm[0];
            scrollRGB[1] = color_lowerArm[1];
            scrollRGB[2] = color_lowerArm[2];
            break;

        case 2:     // upper leg
            scrollRGB[0] = color_upperLeg[0];
            scrollRGB[1] = color_upperLeg[1];
            scrollRGB[2] = color_upperLeg[2];
            break;

        case 3:     // lower leg
            scrollRGB[0] = color_lowerLeg[0];
            scrollRGB[1] = color_lowerLeg[1];
            scrollRGB[2] = color_lowerLeg[2];
            break;

        default:
            break;
        }
    }

    if (control == 2)// 스크롤바 처리
    {
        switch (radio->get_int_val())
        {
        case 0:    // upper arm
            color_upperArm[0] = scrollRGB[0];
            color_upperArm[1] = scrollRGB[1];
            color_upperArm[2] = scrollRGB[2];
            break;

        case 1:     // lower arm
            color_lowerArm[0] = scrollRGB[0];
            color_lowerArm[1] = scrollRGB[1];
            color_lowerArm[2] = scrollRGB[2];
            break;

        case 2:     // upper leg
            color_upperLeg[0] = scrollRGB[0];
            color_upperLeg[1] = scrollRGB[1];
            color_upperLeg[2] = scrollRGB[2];
            break;

        case 3:     // lower leg
            color_lowerLeg[0] = scrollRGB[0];
            color_lowerLeg[1] = scrollRGB[1];
            color_lowerLeg[2] = scrollRGB[2];
            break;

        default:
            printf_s("스크롤바 디폴트");
            break;
        };
    }

//    GLUI_Master.sync_live_all();
}

void anim_cb(int control)
{
    if (control == 1) // start button
    {
//       printf_s("start button || max array size %d \n", anim_array.size());
        isAnimateNow = true;
        current_anim_Index = 0;
        glutTimerFunc(100, AnimTImer, 1);

    }
    else if (control == 2) // stop button
    {
//        printf_s("stop button \n");
        isAnimateNow = false;
        current_anim_Index = 0;
        right_shoulder = 0; right_elbow = 0;
        left_shoulder = 0; left_elbow = 0;
        right_joint = 0; right_knee = 0;
        left_joint = 0; left_knee = 0;
    }

    glutPostRedisplay();
}

void GLUI_Func()
{
    /** Pointers to the windows and some of the controls we'll create **/

    GLUI_Panel* panel_HWSample;
    GLUI_Panel* panel_rot_scale_wireframe;
    GLUI_Panel* panel_transition;
    GLUI_Panel* panel_animation;
    GLUI_Panel* panel_color;


    GLUI_Button* start;
    GLUI_Button* stop;

    //    printf("GLUI version: %3.2f\n", GLUI_Master.get_version());

        /*** Create the side subwindow ***/
    glui = GLUI_Master.create_glui("Menu");

    /***** Control for object params *****/

    panel_HWSample = new GLUI_Panel(glui, "");
    glui->add_statictext_to_panel(panel_HWSample, "HW Sample");
    glui->add_column_to_panel(panel_HWSample);
    edittext = new GLUI_EditText(panel_HWSample, "msg", text);
    edittext->set_w(150);

    panel_rot_scale_wireframe = new GLUI_Panel(glui, "");

    GLUI_Rotation* view_rot = new GLUI_Rotation(panel_rot_scale_wireframe, "Rotate", view_rotate);
    view_rot->set_spin(0.1);
    glui->add_column_to_panel(panel_rot_scale_wireframe);
    (new GLUI_Spinner(panel_rot_scale_wireframe, "Scale:", &scale))
        ->set_float_limits(0.2, 4);
    new GLUI_Checkbox(panel_rot_scale_wireframe, "Wireframe", &isWireModel);


    panel_transition = new GLUI_Panel(glui, "Transition");

    GLUI_Translation* trans_xy =
        new GLUI_Translation(panel_transition, "Objects XY", GLUI_TRANSLATION_XY, obj_pos);
    trans_xy->set_speed(.005);
    glui->add_column_to_panel(panel_transition);

    GLUI_Translation* trans_x =
        new GLUI_Translation(panel_transition, "Objects X", GLUI_TRANSLATION_X, &obj_pos[0]);
    trans_x->set_speed(.005);
    glui->add_column_to_panel(panel_transition);

    GLUI_Translation* trans_y =
        new GLUI_Translation(panel_transition, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1]);
    trans_y->set_speed(.005);
    glui->add_column_to_panel(panel_transition);

    GLUI_Translation* trans_z =
        new GLUI_Translation(panel_transition, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2]);
    trans_z->set_speed(.005);
    glui->add_column_to_panel(panel_transition);

    panel_animation = new GLUI_Rollout(glui, "Animation Control", true);
    start = new GLUI_Button(panel_animation, "Start", 1, anim_cb);
    glui->add_column_to_panel(panel_animation);
    start = new GLUI_Button(panel_animation, "Stop", 2, anim_cb);

    panel_color = new GLUI_Rollout(glui, "Custom Color", true);

    radio = new GLUI_RadioGroup(panel_color, &select_color, 1, color_cb);
    new GLUI_RadioButton(radio, "Upper Arm");
    new GLUI_RadioButton(radio, "Lower Arm");
    new GLUI_RadioButton(radio, "Upper Leg");
    new GLUI_RadioButton(radio, "Lower Leg");
    GLUI_Scrollbar* sb;
    sb = new GLUI_Scrollbar(panel_color, "Red", GLUI_SCROLL_HORIZONTAL, &scrollRGB[0], 2, color_cb);
    sb->set_float_limits(0, 1);
    sb = new GLUI_Scrollbar(panel_color, "Green", GLUI_SCROLL_HORIZONTAL, &scrollRGB[1], 2, color_cb);
    sb->set_float_limits(0, 1);
    sb = new GLUI_Scrollbar(panel_color, "Blue", GLUI_SCROLL_HORIZONTAL, &scrollRGB[2], 2, color_cb);
    sb->set_float_limits(0, 1);
    scrollRGB[0] = color_upperArm[0];
    scrollRGB[1] = color_upperArm[1];
    scrollRGB[2] = color_upperArm[2];


    GLUI_Listbox* list = new GLUI_Listbox(glui, "Background Color ", &clear_color);
    for (int i = 0; i < 5; i++)
        list->add_item(i, string_list[i]);

    glui->add_separator();
    new GLUI_Button(glui, "Exit", 0, (GLUI_Update_CB)exit);


}

void updateAnimInfo(animInfo& info, const std::string& part, int value) {
    if (part == "lll") info.left_lower_leg = value;
    else if (part == "lul") info.left_upper_leg = value;
    else if (part == "lua") info.left_upper_arm = value;
    else if (part == "lla") info.left_lower_arm = value;
    else if (part == "rll") info.right_lower_leg = value;
    else if (part == "rul") info.right_upper_leg = value;
    else if (part == "rua") info.right_upeer_arm = value;
    else if (part == "rla") info.right_lower_arm = value;
}

void readFile()
{
    std::ifstream infile("RobotStory.txt");
    if (!infile) {
        std::cerr << "Unable to open file";
        return; // Exit if the file can't be opened
    }

    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int index, value;
        std::string part;

        if (!(iss >> index >> part >> value)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue; // Skip malformed lines
        }

        // Assuming index is 1-based, adjust for 0-based array indexing
        if (index >= 0 && index <= anim_array.size()) {
            updateAnimInfo(anim_array[index], part, value);
        }
        else {
            std::cerr << "Index out of bounds: " << index << std::endl;
        }
    }

    infile.close();


    //for (size_t i = 0; i < anim_array.size(); ++i) {     // Example: Print the results to verify
    //    const animInfo& info = anim_array[i];
    //    std::cout << "Index " << i << ": "
    //        << "roate_upper_right_arm = " << info.right_upeer_arm << ", "
    //        << "roate_lower_right_arm = " << info.right_lower_arm << ", "
    //        << "roate_upper_right_leg = " << info.right_upper_leg << ", "
    //        << "roate_lower_right_leg = " << info.right_lower_leg << ", "
    //        << "roate_upper_left_arm = " << info.left_upper_arm << ", "
    //        << "roate_lower_left_arm = " << info.left_lower_arm << ", "
    //        << "roate_upper_left_leg = " << info.left_upper_leg << ", "
    //        << "roate_lower_left_leg = " << info.left_lower_leg << std::endl;
    //}
}

void AnimTImer(int Value)
{
    if (!isAnimateNow) return;

    right_shoulder = anim_array[current_anim_Index].right_upeer_arm;
    left_shoulder = anim_array[current_anim_Index].left_upper_arm;

    right_elbow = anim_array[current_anim_Index].right_lower_arm;
    left_elbow = anim_array[current_anim_Index].left_lower_arm;

    right_joint = anim_array[current_anim_Index].right_upper_leg;
    left_joint = anim_array[current_anim_Index].left_upper_leg;

    right_knee = anim_array[current_anim_Index].right_lower_leg;
    left_knee = anim_array[current_anim_Index].left_lower_leg;

    current_anim_Index++;
    if (current_anim_Index >= anim_array.size()) current_anim_Index = 0;

    glutPostRedisplay();
    glutTimerFunc(500, AnimTImer, 1);
}

int main(int argc, char** argv) {
    readFile();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    main_window = glutCreateWindow("Robot HW");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);

    glutTimerFunc(500, AnimTImer, 1);

    GLUI_Func();

    glui->set_main_gfx_window(main_window);
    GLUI_Master.set_glutIdleFunc(myGlutIdle);

    glutMainLoop();
    return 0;
}