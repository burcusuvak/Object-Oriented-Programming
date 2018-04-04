/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
        
package gtusetınt_test;

import java.lang.reflect.Array;
import java.util.Arrays;
/**
 *  GTUSet class i GTUSetInt interface inden implement edilir
 * @author Burcu SUVAK OZTURK 141044079
 * 
 */

public class GTUSet<T> implements GTUSetInt<T>{
    
    public class GTUIterator<T>{
               
       private int currentIndex = 0;
       private int currentSize;
       
       public GTUIterator(){           
           currentSize = capacity;           
       }
       
        /**
        * @return currentIndex kapasiteden den kucukse true degilse false return eder
        */       
       public boolean hasNext(){
           
           return  currentIndex < currentSize && container[currentIndex] != null ;
       }
       
       /**
        * 
        * @return currentIndex 0 dan buyukse true degilse false return eder
        */       
       public boolean hasPrevious(){
            
           return currentIndex > 0;
       }
       
       /**
        * hasPrevious() fonksiyonu true dondururse bir oncesindeki eleman return edilir
        * @return iteratorun mevcut konumundan bir onceki elemani return eder
        */          
       public T previous(){
            if ( hasPrevious() )
                return (T)container[--currentIndex];
            else
                return null;           
       }
       
       /**
        *  hasNext() fonksiyonu true dondururse bir oncesindeki eleman return edilir
        * @return iteratorun mevcut konumundan sonraki elemani return eder
        */       
       public T next(){
            //if( "gtusetınt_test.GTUSet".equals(this.getClass().getName())  ) 
            if ( hasNext() )
                return (T)container[++currentIndex];
            else 
                return null;                                  
       } 
       
       /**
        * @return iteratorun konumlandigi index teki degeri dondurur
        */       
       public T getItem(){
           
           return (T)container[currentIndex];
       }
                
    }
    
    private int used;
    private int capacity;
    private final int increase;
    private Object[] container;

 /**
 * @param capacityValue Set in sahip oldugu maksimum eleman sayisi
 */
    public GTUSet(int capacityValue){
        capacity = capacityValue;
        used = 0;
        increase = 10;
        container = new Object[capacityValue];
    }
    /**
     * GTUSet class Constructor
     */
     public GTUSet(){
        capacity = 50;
        used = 0;
        increase = 10;        
        container = new Object[capacity];
    }
       
    /**
     *     
     * @return Set in kapasitesini döndürür
     */
    public int max_size(){      return capacity;    }
    
    /**
     * 
     * @return getUsed() Set içinde bulunan eleman sayısını döndürür
     */
    public int size(){  return getUsed();       }
    
    /**    
     * @return Set içinde bulunan eleman sayısını döndürür
     */
    
    public int getUsed(){
        return used;
    }
    /**
     *  Set in eleman sayısnı bir artırır.
     */
    public void setUsed(){
        ++used;       
        
    }
    
    /**
     * kapasite doldugunda Set in kapasite degerini arttrır.
     */
    public void setCapacity(){
        capacity += increase;
    }
    
    /**     
     * @return Set boş ise true degilse false döndürür
     */    
    @Override
    public boolean empty(){
        
        return getUsed() == 0;             
    }
    
    /**
     *  Set in tüm içeriğini temizler
     */
    @Override
    public void clear(){    
        container = null;
        used = 0;
    }
    
    /**
     *  insert() fonksiyonu set e eklanmek istenen eleman 
     *  eger set icinde mevcut degilse value degerini
     *  set e ekler ve used degerini bir artırır
     *  daha sonra elamanı uygun yere yerlestirebilmak için
     *  sort() fonksiyonunu cagırır ve kucukten buyuge
     *  sıralama isini yapar
     *  ancak set icinde bu eleman zaten 
     *  varsa bir invalid_value exception fırlatır
     * 
     * @param value set e eklamek istenilen deger
     */
    
    @Override
    public void insert(T value) throws IllegalArgumentException{

        int found = 0;
        
        if( getUsed() >= capacity ){
            setCapacity();
            System.out.println("\nTaking extra space...");
            Object[] backUpArray;
            
            backUpArray = new Object[getUsed()];
            for(int i = 0; i < getUsed(); ++i)
                backUpArray[i] = container[i];
            container = new Object[getUsed() + increase];
            
            for(int i = 0; i < getUsed(); ++i)
                container [i] = backUpArray[i];            
            
        }

        for( int i = 0; i < getUsed(); ++i ){
            if( container[i] == value )
                found = 1;  
        }                
               
        if( found == 0 ){
            container[getUsed()] = value;
            setUsed();
        }
        else
            throw new IllegalArgumentException("Invalid input...\n");
        
        sort();
    }
    
    /**
     *  printSet() set in tüm elemanlarını ekrana basar
     */
    public void printSet(){
        
        System.out.println(java.util.Arrays.toString( container ));
    }
   
    /**
    *   sort() fonksiyonu array eleman eklendikten sonra
    *   elemanları kücükten büyüğe dogru sıralar
    */    
    @Override
    public void sort(){
        
        Arrays.sort(container,0,getUsed());       
    }
    /**
     *  erase() fonksiyonu parametre olarak aldıgı value degeri 
     *  set in icinde varsa onu siler ve used degerini bir azaltır
     * @param value Setten silinmek istenen değer 
     */    
    @Override
    public void erase(Object value){
                
	for ( int i = 0; i < getUsed() ; ++i ){
            if ( container[i] == value )
            {	
                --used;
                
		for (int j = i; j < getUsed(); ++j)	                 
                    container[j] = container[j+1];                  	
				
            }
            container[getUsed()] = null;
	} 
   }
    
    /**
     * İntersection() fonksiyonu iki adet Set i karşılaştırır ve 
     * kesişimlerini döndürür.
     * @param other GTUSet objesi referansı
     * @return intersection objesini return eder
     */
    @Override
    public GTUSet<T> intersection(GTUSet<T> other){
        Object[] arr;
        int size;
        if ( this.getUsed() <= other.getUsed() )
            size = this.getUsed();
	else
            size = other.getUsed();
        arr = new Object[size];
        
        System.out.print("INTERSECTION : ");
        
        if ( this.getUsed() <= other.getUsed() ){
            for (int i = 0; i < this.getUsed(); ++i)
            {	
		for (int k = 0; k < other.getUsed(); ++k)
		{
                    if ( container[i] == other.container[k] )
                    {
			arr[i] = container[i];
      			System.out.printf("%d ",container[i]);

                    }
		}			                
            }
	}
        
        else{
            for (int i = 0; i < other.getUsed(); ++i)
            {	
		for (int k = 0; k < this.getUsed(); ++k)
		{
                    if ( other.container[i] == container[k] )
                    {
			arr[i] = other.container[i];
			System.out.printf("%d ",other.container[i]);
                    }
		}	
            }
	}        
        System.out.println();
        return other;
   }
    
    /**
     * @return container Set in referansını döndürür
     */   
    public Object[] returnItems(){
       
       return container;
    }
    
    /**
     * Bulunmak istenen degeri alır ve eger bulursa ıteratorunu dondurur
     * bulamazsa null return eder
     * @param theValue Set icinde bulunmak istenen deger
     * @return bulundugu yerin iteratoru
     */    
    @Override
    public GTUIterator<T> find(Object theValue){
        
        GTUIterator<T> iter = new GTUIterator();
        
        boolean found = false;

            for (int i = 0; i < getUsed() ; ++i)
            {   
		if( theValue == container[i] ){
                    found = true;
		}
                if(!found)

                    iter.next();

            }
                return iter;               
    }       
    
    public GTUIterator<T> begin(){
        
        GTUIterator<T> iter = new GTUIterator();

        return iter;
    }
       
    public GTUIterator<T> end(){
        
        GTUIterator<T> iter = new GTUIterator();
        for(int i = 0; i < getUsed()-1; ++ i)
            iter.next();
        return iter;
    }
}

