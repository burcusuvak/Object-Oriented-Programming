/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gtusetınt_test;
/**
 *
 * @author burcu
 */
import javafx.util.Pair;
import javax.xml.transform.Source;

public class GTUSetInt_Test {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        GTUSet<Integer> set1 = new GTUSet(6);
       
        System.out.printf("Capacity: %d\n",set1.max_size());

        try{
            set1.insert(2);
            set1.insert(5);
            set1.insert(7);
            set1.insert(1);
            set1.insert(0);
            set1.insert(3);
            
            System.out.print("SET A: ");
            set1.printSet();

            System.out.print("Add a new element !");
            set1.insert(8);
            System.out.printf("New capacity: %d\n",set1.max_size());

            System.out.print("NEW SET A: ");
            for( int i = 0; i < set1.getUsed(); ++i )
                System.out.printf("%d  ",set1.returnItems()[i]);          
            System.out.println("\n__________________________________");

            GTUSet<Integer> set2 = new GTUSet(5);

            set2.insert(9);
            set2.insert(3);
            set2.insert(7);
            set2.insert(1);
            set2.insert(4);  

            System.out.print("\n\nSET B: ");
            set2.printSet();

            System.out.print("Set A and Set B ");
            set1.intersection(set2); 
            System.out.println("__________________________________\n");

            System.out.print("SET A: ");       
            for( int i = 0; i < set1.getUsed(); ++i )
                System.out.printf("%d  ",set1.returnItems()[i]); 

            set1.erase(0);
            int lastIndex = set1.getUsed()-1;
            System.out.printf("\n0 was deleted.\nSET A: ");
            for( int i = 0; i < set1.getUsed(); ++i )
                System.out.printf("%d  ",set1.returnItems()[i]); 

            set1.erase(3);
            System.out.printf("\n3 was deleted.\nSET A: ");
            for( int i = 0; i < set1.getUsed(); ++i )
                System.out.printf("%d  ",set1.returnItems()[i]);                      
            System.out.println("\n__________________________________\n");      

            //GTUSet<String> myset = new GTUSet<String>(String[].class,3);
            GTUSet<String> myset = new GTUSet(3);

            System.out.println("String set creating ");

            myset.insert("Cinar");
            myset.insert("Burcu");
            myset.insert("London");
            System.out.print("SET 1:  ");               
            myset.printSet();
            System.out.println("\n__________________________________");

            System.out.println("Burcu was deleted ");
            myset.erase("Burcu");
            System.out.print("SET 1:  "); 
            for( int i = 0; i < myset.getUsed(); ++i )
                System.out.printf("%s  ",myset.returnItems()[i]);  
            System.out.println();  
            System.out.println("\n__________________________________");

            System.out.println("SET A completely cleaning...");  
            set1.clear();
            for( int i = 0; i < set1.getUsed(); ++i )
                System.out.printf("%d  ",set1.returnItems()[i]); 
            System.out.print("\nSET A: ");               
            System.out.println("\n__________________________________\n");

            GTUMap<Integer,Integer> map1 = new GTUMap(3);
            map1.insert(4,5);
            map1.insert(9,10);
            System.out.print("\nMAP A: ");               
            for( int i = 0; i < map1.getUsed(); ++i ){
                System.out.printf("  ");
                System.out.print(map1.returnMapItems()[i]);
            }  
            System.out.println("\nKey value 9 was cleaned and added a new element...");               
            map1.erase(9);        
            map1.insert(7,8);
            System.out.print("\nMAP A: ");               
            for( int i = 0; i < map1.getUsed(); ++i ){
                System.out.printf("  ");
                System.out.print(map1.returnMapItems()[i]);
            }
            System.out.println("\n__________________________________\n");

            System.out.print("7 matching: ");  
            System.out.println(map1.at(7));  
            GTUMap<Integer,Integer> map2 = new GTUMap(3);
            map2.insert(4,5);
            map2.insert(7,5);
            System.out.print("\nMAP B: ");               
            for( int i = 0; i < map2.getUsed(); ++i ){
                System.out.printf("  ");
                System.out.print(map2.returnMapItems()[i]);
            } 
            System.out.println();        
            map1.intersection(map2);
            System.out.println("\n__________________________________\n");

            GTUSet<Integer>.GTUIterator<Integer> inner_G1 = set2.new GTUIterator<Integer>();
            inner_G1.hasNext();

            System.out.print("SET B traversing starts..\n");
            System.out.println("First element is " + inner_G1.next());
            System.out.println("Next element from 3: " + inner_G1.next());

            System.out.println("\n__________________________________\n");
            System.out.print("Next element from 7:  ");
            System.out.println(set2.find(7).next());
            System.out.println("Previos element from 9 is " + set2.find(9).previous());
            System.out.println("\n__________________________________\n");

            System.out.println("Iterator goes to SET B end  : " + set2.end().getItem());
            System.out.println("Iterator goes to SET B begin  : " + set2.begin().getItem());
            System.out.println("\n__________________________________\n");

            map2.insert(17,21);
            System.out.printf("MAP B capacity:  %d",map2.getCapacity());

            map2.insert(88,77);
            System.out.printf("MAP B:");
            
            for( int i = 0; i < map2.getUsed(); ++i ){
                System.out.printf("  ");
                System.out.print(map2.returnMapItems()[i]);
            } 
            
            System.out.printf("\nMAP B new capacity:  %d",map2.getCapacity());                       
            System.out.println("\n__________________________________\n"); 
            
            GTUMap<Integer,Integer>.GTUIterator<Integer> inner_G3 = map2.new GTUIterator<Integer>();           

            System.out.println("TESTING EXCEPTION...");            
            map2.insert(4,5);            

        }
       
        catch(IllegalArgumentException e){
            System.out.println();
            System.out.print(e);
        }
       
    }
            
}
