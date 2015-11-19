#include "Graph.h"
#include "Simple_window.h"
using namespace Graph_lib;

// Graph.h�����Graph.cpp�Ƀe�L�X�g�x�[�X�̏o�̓t�H�[�}�b�g�̂��߂̃R�[�h��ǉ�
// OBJ_TEXT����`����Ă���Ƃ��̂݁A�h���N���X�̃R���X�g���N�^���Ŏ��s�����

int main() {
	Simple_window win(Point(100, 100), 600, 400, "GUI textbase output");

	Vector_ref<Shape> vr;
	vr.push_back(new Line(Point(250, 250), Point(350, 350)));
	vr.push_back(new Graph_lib::Rectangle(Point(100, 300), 50, 50));
	vr.push_back(new Graph_lib::Rectangle(Point(250, 250), Point(350, 350)));
	vr.push_back(new Circle(Point(100, 100), 50));
	vr.push_back(new Graph_lib::Ellipse(Point(100, 100), 20, 40));
	vr.push_back(new Text(Point(350, 350), "test"));
	
	for(int i = 0; i < vr.size(); ++i)
		win.attach(vr[i]);

	win.wait_for_button();
}