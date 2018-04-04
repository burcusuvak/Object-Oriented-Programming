/**
 * CSE241  HW8
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package conncetfourgui;

import java.awt.*;
import static java.awt.Color.BLUE;
import static java.awt.Color.RED;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.border.*;

/**
 * 
 * @author Burcu SUVAK OZTURK  141044079
 */
public class Gui {
    
    private JFrame jf, jfConnect4;
    private JTextField txt, txt3;
    private JButton button;
    private JButton[] buttons;
    private JLabel[][] buttonGroup;
    private JLabel jlab, jlab3;
    private JPanel jp;
    private int height, width;
    char choice;
    Color color;
    char turn;
    private int c=0;
    private int count = 0;
    private int total;

    public Gui()  {
        
        jf = new JFrame();
        jf.setSize(300,300);
        jf.setBackground(Color.pink);
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.getContentPane().setLayout(new FlowLayout());              
            
        JLabel lbl = new JLabel("Please enter 4 - 20 for Board Size");
        lbl.setHorizontalAlignment(JLabel.CENTER);
        jf.getContentPane().add(lbl);
        txt = new JTextField(10);
        jf.add(txt);
        jlab = new JLabel("BOARD HEIGHT");
        jlab.setHorizontalAlignment(JLabel.CENTER);
        jf.getContentPane().add(jlab); 
        
        
        txt3 = new JTextField(10);
        jf.add(txt3);
        jlab3 = new JLabel("GAME TYPE: P / C");
        jlab3.setHorizontalAlignment(JLabel.CENTER);
        
        jf.getContentPane().add(jlab3);
        
        button = new JButton("ENTER");
        button.setBackground(Color.pink);
        button.setHorizontalAlignment(JButton.CENTER);
        jf.getContentPane().add(button);
           
        button.addActionListener((ActionEvent e) -> {
            jlab.setText("Height : " + txt.getText());
            jlab3.setText("Game type : " + txt3.getText());
            height = Integer.parseInt(txt.getText());
            width = Integer.parseInt(txt.getText());
            choice = txt3.getText().charAt(0);
            this.Connect4(height, width);

        }); 
        
        jf.setVisible(true);        
    }
    
    /**     
     * Board en ve boyu eşit olmalıdır
     * @return board size
     */
    public int getHeight(){ return height;  }
    
    /**     
     * @return board size
     */
    public int getWidth(){ return width;  }

    /**
     * Siranin kimde olduguna bakar ve ona gore
     * Tas rengini degistirir
     */
    public void setColor(){
        if(get_turn() == '1')
            color = BLUE;          
              
        if(get_turn() == '2' )        
            color = RED;                          
    }

    /**
     * Siranin kimde oldgunu set eder
     * @param playTurn Oynama sirasinin kime ait oldugu
     */
    public void set_turn( char playTurn )
    {
	if ( playTurn == '1' || playTurn == '2')	
            turn = playTurn ;		
    }        
    
    /**     
     * @return Oyunda siranin kimde oldugunu return eder
     */
    public char get_turn(){     return turn;    }

    /**     
     * @return JLabel lerin yani oyun hücrelerinin rengini return eder
     */
    public Color getColor(){
        return color;
    }
    
    /**    
     * @param i row
     * @param input column
     * @return Oyun hücresi bos yani WHITE ise true degilse false return eder
     */
    public boolean isEmpty( int i, int input){        
	boolean empty;

	if( buttonGroup[i][input].getBackground() == Color.WHITE )
            empty= true ;
	else
            empty= false;

	return empty;
    }                          
    
    /**
     * Dikey line larda 4 lu olup olmadigina bakar
     * @return oyun bitmisse true return eder aksi taktirde false retun edecektir
     */       
    public int verticalCheck(){
        int four = 4;
        int lastControlColumn = getWidth()-3;        

        for(int i = 0; i < getHeight(); ++i){
            for(int j = 0; j < lastControlColumn; ++j){
                int foundRed = 0, foundBlue = 0; 
                int k = 0;
                while( k < four ){
                    if( buttonGroup[i][j+k].getBackground() == Color.RED ) 
                        ++foundRed;
                       
                    else if(buttonGroup[i][j+k].getBackground() == Color.BLUE)
                        ++foundBlue;
                    
                    ++k;
                }
                if( foundRed == four)                   
                    return 1;                
                if( foundBlue == four)                           
                    return 2;                
            }    
        }

        return 0;
    }
    
    /**
     * Yatay line larda 4 lu olup olmadigina bakar
     * @return KIRMIZI oyuncu kazanirsa 1 BLUE kazanirsa 2 return eder
     */    
    public int horizontalCheck(){
        int four = 4;
        int lastControlRow = getWidth()-3; 
        
        for(int j = 0; j < getWidth(); ++j){
            for(int i = 0; i < lastControlRow; ++i){
                int foundRed = 0, foundBlue = 0; 
                int k = 0;
                while( k < four ){
                    if( buttonGroup[i+k][j].getBackground() == Color.RED ) 
                        ++foundRed;
                       
                    else if(buttonGroup[i+k][j].getBackground() == Color.BLUE)
                        ++foundBlue;
                    
                    ++k;
                }
                if( foundRed == four)                   
                    return 1;                
                if( foundBlue == four)                           
                    return 2;                
            }    
        }
        
        return 0;
    }
    
    /**
     * 
     * Capraz line da 4 lu olup olmadigina bakar
     * @return KIRMIZI oyuncu kazanirsa 1 BLUE kazanirsa 2 return eder
     */
    public int DiagonalCheck(){
        int four = 4;
        int foundRed = 0, foundBlue = 0, foundR = 0, foundB = 0;
	
        for( int j= getHeight()-4, c=0; j > 0 && c < getHeight() -3; -- j, ++c)
	{   	
            int i=0, sayac=0 ;
            while( sayac <= c )
            {
                for( int  k=0; k < four ; ++k )
		{	
                    if( buttonGroup[ i + sayac ][ j + sayac].getBackground() == Color.RED )
                        ++foundRed;
                    if( buttonGroup[ i + sayac ][ j + sayac].getBackground() == Color.BLUE )
                        ++foundBlue;

                    ++i;
                    ++j;
                }
                i -= 4;
		j -= 4;
		++sayac;
                if( foundRed == 4 )
                    return 1;
                if( foundBlue == 4 )
                    return 2;
            }
        }                          
        
        return 0;
    }
    
    /**
     * Vertical, Horizontal ve Diagonal check yapan fonksiyonlari cagirir
     * oyun bitisi varmi diye kontrol eder
     * ayrica board dolduysa ve kazanan yoksa bunu da kontrol eder
     * Eger oyun bitmisse kimin kazandigini bidirir
     * veya kimse kazanmadigi halde board dolmussa kazanan olmadigini bildirir
     * @return oyun bittiyse true bitmediyse false return eder
     */
    public boolean endGame(){
        total = height * width;
        JFrame jFrame = new JFrame("GAME OVER");
        jFrame.setSize(300,300);        
                
        if( count == total ){
            JLabel label = new JLabel("NO WINNER !!!");
            label.setHorizontalAlignment(JLabel.CENTER);
            jFrame.getContentPane().add(label);  
            jFrame.setVisible(true);
            return true; 
            
        }    
        else if( verticalCheck() == 1 || horizontalCheck() == 1 || DiagonalCheck() == 1 ){
            JLabel label = new JLabel("CONGRATULATIONS RED PLAYER WON !!!");
            label.setHorizontalAlignment(JLabel.CENTER);
            jFrame.getContentPane().add(label);  
            jFrame.setVisible(true);            
            return  true;            
        }
        else if( verticalCheck() == 2 || horizontalCheck() == 2 || DiagonalCheck() == 2){
            JLabel label = new JLabel("CONGRATULATIONS BLUE PLAYER WON !!!");
            label.setHorizontalAlignment(JLabel.CENTER);
            jFrame.getContentPane().add(label); 
            jFrame.setVisible(true);
            return true;
        }
            
        else
            return false;
    }    
    
    
    /**
     * Oyunu oynatan fonksiyondur
     * @param value Uzerine tiklanan butonun index degeri
     * @return oyun bittiyse true return eder
     */  
    public int play(int value){
	int RoWsize = height - 1 ;
	boolean control = false;
	boolean legal = false;
	while(  control != true )
	{	
            while( legal != true && RoWsize >= 0 && count <= height*height)
            {   
                legal= isEmpty( RoWsize, value);                
                --RoWsize;
            }
            control = legal;
            
            if( legal == true ){               
                ++count;
                buttonGroup[RoWsize + 1][value].setOpaque(true);
                buttonGroup[RoWsize + 1][value].setBackground(getColor());
                
            } 
            if(endGame())
                return 1;
            
            if(RoWsize<0){
                control =true;
                --c;
            }  
            
        } 
                 
        return 0;
    }
    
    /**
     * Satir ve sutun sayisina gore board hucrelerini olusturur ve hepsini 
     * White olarak ilklendirir
     * Oyunu oynatan play() fonksiyonu burada cagirilir
     * @param _height board boyu
     * @param _width board eni
     */
    public void Connect4(int _height, int _width){
        jfConnect4 = new JFrame("***  WELCOME TO CONNECT FOUR  ***");
        jfConnect4.setSize(800,800);
        jfConnect4.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jp = new JPanel();
        jp.setLayout(new GridLayout(_height + 1,_width));
        
        buttons = new JButton[height];
        for(int i = 0; i < _height; ++i){            
            buttons[i] = new JButton();
            buttons[i].setName(String.valueOf(i));
            buttons[i].setActionCommand("" + i);
            buttons[i].setIcon(new ImageIcon("index.png"));
            buttons[i].addActionListener((ActionEvent e) -> {
                    System.out.println(c);
                    ++c;
                    int input = Integer.parseInt(e.getActionCommand());

                    if(c%2 == 0){
                        set_turn('1');
                        setColor();
                    } 
                    else{
                        set_turn('2');
                        setColor();
                    }
                    int won=0;
                    if( choice == 'p' || choice == 'P' )
                        won = this.play(input);
                    
                    
                
            });
            
            jp.add(buttons[i]);
        }
                
        buttonGroup = new JLabel[_height][_width];
        
        for(int i = 0; i < _height; ++i){
            for(int j = 0; j < _width; ++j){
                buttonGroup[i][j] = new JLabel();                
                buttonGroup[i][j].setBorder(new LineBorder(Color.pink));  
                buttonGroup[i][j].setBackground(Color.WHITE);
                jp.add(buttonGroup[i][j]);
            }                   
        }                
                
        jfConnect4.getContentPane().add(jp);

        jfConnect4.setVisible(true);            
            
            
        }              
    
}
