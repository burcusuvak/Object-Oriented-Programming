/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gtusetınt_test;

/**
*
* @author burcu
 * @param <T> generate type
*/
public interface GTUSetInt <T>{
    
    boolean empty();
    int size();
    int max_size();
    void clear();
    void insert(T value) throws IllegalArgumentException;
    void sort();
    void erase(Object value);
    GTUSet<T> intersection(GTUSet<T> other);
    GTUSet<T>.GTUIterator<T> find(Object theValue);
    void setCapacity();
}
