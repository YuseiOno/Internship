package draw;

import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
public class mouse extends Frame implements MouseListener,MouseMotionListener {
	int x0,y0;  //始点のx,y座標
	
	//コンストラクタ
	public mouse() {
		setSize(400,300);
		addMouseListener(this);
		addMouseMotionListener(this);
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
	}
	//paint
	public void paint(Graphics g) {
	}
	//マウスが押されたら
	public void mousePressed(MouseEvent e) {
		//始点の保存
		x0=e.getX();
		y0=e.getY();
	}
	//マウスが離されたら
	public void mouseReleased(MouseEvent e) {
	}
	//マウスがクリックされたら
	public void mouseClicked(MouseEvent e) {
	}
	//マウスが画面に入ったら
	public void mouseEntered(MouseEvent e) {
	}
	//マウスが画面から出たら
	public void mouseExited(MouseEvent e) {
	}
	//マウスがドラッグされたら
	public void mouseDragged(MouseEvent e) {
		//線を引く
		Graphics g=getGraphics();
		g.drawLine(x0, y0, e.getX(), e.getY());
		g.dispose();
		//次のために始点を更新
		x0=e.getX();
		y0=e.getY();
	}
	//マウスが動いたら
	public void mouseMoved(MouseEvent e) {
	}
	//main
	public static void main(String[] args) {
		Frame w=new mouse();
		w.show();
	}
}
