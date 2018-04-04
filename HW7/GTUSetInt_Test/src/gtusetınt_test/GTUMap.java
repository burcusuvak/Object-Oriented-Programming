/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gtusetınt_test;

import javafx.util.Pair;

/**
 *
 * @author burcu
 * @param <K> Key degeri
 * @param <V> Value degeri
 */
public class GTUMap<K,V> extends GTUSet< javafx.util.Pair<K,V> > {
   
    private Pair<K,V>[] newPair;
    private int _capacity;
    private int _used;
    private int _increase = 10;

    public GTUMap(){
       _capacity = 20;
       _used = 0;
       newPair = new Pair[_capacity];
       
    }
    public GTUMap(int capacityValue) {
       _capacity = capacityValue;
       _used = 0;
       newPair = new Pair[_capacity];
       
    }
    /**
     *     
     * @return Map içinde bulunan eleman sayısını döndürür
     */    
    @Override
    public int getUsed(){
        return _used;
    }   
    
    /**
     * kapasite doldugunda Set in kapasite degerini arttrır.
     */
    @Override
    public void setCapacity(){
        _capacity += _increase;
    }
    
    public int getCapacity(){
        return _capacity;
    }
    
    /**
     *  insert() fonksiyonu Map e eklanmek istenen eleman 
     *  eger Map icinde mevcut degilse value degerini
     *  Map e ekler ve _used degerini bir artırır     
     *  ancak Map icinde bu eleman zaten 
     *  varsa bir invalid_value exception fırlatır
     * 
     * @param theKey eklenmek istenen key degeri
     * @param theValue set e eklamek istenilen deger
     */      
    public void insert(K theKey, V theValue){
        
        Pair p1 = new Pair(theKey,theValue);        
        
        int found = 0;
                
        if( getUsed() >= _capacity ){
            setCapacity();
            System.out.println("\nTaking extra space...");
            
            Pair<K,V>[] newArray = new Pair[getUsed()];

            for(int i = 0; i < getUsed(); ++i)
                newArray[i] = newPair[i];
            
            newPair = new Pair[getUsed() + _increase];
            
            for(int i = 0; i < getUsed(); ++i)
                newPair [i] = newArray[i];            
            
        }        
        
        for(int i = 0 ; i < _used; ++i ){
            if( newPair[i].getKey() == theKey )
                found = 1;
        }
        if( found == 0 ){
            
            newPair[_used] = p1;
            ++ _used;            
        }
        else
            throw new IllegalArgumentException("Invalid key value...\n");
    }
    
    public void printMap(){
        
        System.out.print("MAP:  ");
        System.out.println(java.util.Arrays.toString( newPair ));        
    }
    
     public Object[] returnMapItems(){
       
       return newPair;
    }
    
    public V at(K theKey){
        int found = 0;
        int index = 0;
        
        for(int i = 0; i < _used; ++i ){
            if( newPair[i].getKey() == theKey ){         
                found = 1;
                index = i;
            }    
        } 
        if (found == 1)
            return  (newPair[index].getValue());
        else
            return null;                          
    }
    /**
     * eraseMap() fonksiyonu verilen key e ait value yu
     * Map ten siler ve _used u bir eksiltir
     * @param theKey silinmek istenen value ya ait key
     */
    
    public void erase(Object theKey){
        
        for(int i = 0 ; i < _used; ++i ){
            if( newPair[i].getKey() == theKey ){             
                
                newPair[i] = null;
                -- _used;                
            }    
        }                
        
    }
    
    GTUMap<K,V> intersection(GTUMap<K,V> other){
        Pair<K,V>[] arr;
        int size;
        if ( this.getUsed() <= other.getUsed() )
            size = this.getUsed();
	else
            size = other.getUsed();
        arr = new Pair[size];
        System.out.print("INTERSECTION : ");
        
        if ( this.getUsed() <= other.getUsed() ){
            for (int i = 0; i < this.getUsed(); ++i)
            {	
		for (int k = 0; k < other.getUsed(); ++k)
		{
                    if ( newPair[i].getKey() == other.newPair[k].getKey() && newPair[i].getValue() == other.newPair[k].getValue() )
                    {   
			arr[i] = newPair[i];
      			System.out.print(newPair[i]);

                    }
		}			                
            }
	}
        
        else{
            for (int i = 0; i < other.getUsed(); ++i)
            {	
		for (int k = 0; k < this.getUsed(); ++k)
		{
                    if ( newPair[i].getKey() == other.newPair[k].getKey() && newPair[i].getValue() == other.newPair[k].getValue() )
                    {  
			arr[i] = other.newPair[i];
			System.out.print(other.newPair[i]);
                    }
		}			
            }

	}
        
        System.out.println();                
      
        return other;
    }    
    
    @Override
    public GTUIterator<Pair<K,V>> find(Object theKey){
        
        GTUIterator<Pair<K,V>> iter = new GTUIterator();
        
        boolean found = false;

        for (int i = 0; i < getUsed()-1 ; ++i)
        {   
            if( theKey == newPair[i].getKey() ){
                
                found = true;
            }
            if(!found)
               iter.next();
        }
        return iter;               
    }        
    
}
