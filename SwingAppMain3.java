package gui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class SwingAppMain3 {

	public static void main(String[] args) {
		// TODO 自動生成されたメソッド・スタブ
		JFrame mainFrame=new JFrame("SwmngApptテキスト入力");
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setSize(320,160);
		mainFrame.setLocationRelativeTo(null);
		
		Container contentPane=mainFrame.getContentPane();
		
		//テキスト入力場所のインスタンスを生成
		final JTextField textField=new JTextField();
		final JTextArea textArea=new JTextArea(5,0);
		
		//スクロールペインにテキストエリアを追加
		JScrollPane scrollPane=new JScrollPane(textArea);
		JButton button=new JButton("テキスト追加");
		//button.setAction();
		
		//アクションの定義
		button.addActionListener(new AbstractAction() {
			public void actionPerformed(ActionEvent arg0) {
				textArea.append(textField.getText()+"\n");
			}
		});
		
		//パネルをコンポーネントに配置
		contentPane.add(textField,BorderLayout.NORTH);
		contentPane.add(scrollPane,BorderLayout.CENTER);
		contentPane.add(button,BorderLayout.SOUTH);
		
		mainFrame.setVisible(true);
	}

}
