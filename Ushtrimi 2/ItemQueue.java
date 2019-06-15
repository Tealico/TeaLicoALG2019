//Krijojme nje klas ItemQueue e cila do te mbaje nje
//rradhe me Objekte te tipit Item, pra do te mbaje
//nje rradhe me elemente ku secili element ka
//thellesine dhe url-ne e tij

import java.util.ArrayList;

public class ItemQueue {
    private ArrayList<Item> items;

    public ItemQueue() {
        items = new ArrayList<>();
    }

    /**
     * Metoda enqueue(Item item) Shton nje Item ne rradhe
     * ne qofte se eshte e mundur, eshte e mundur ne qofte se rradha
     * nuk e permban ate Item, kthen true nqs perfundon me sukses.
     * kthen false nqs Item ndodhet ne rradhe, pra ai nuk mund te shtohet
     * */
    public boolean enqueue(Item item) {
        if(items.contains(item))
            return false;
        items.add(items.size(),item);
        return true;
    }

    /**
     * Heq koken e rradhes nese rradha nuk eshte bosh
     * dhe e kthen ate ose kthen null ne qofte se rradha eshte bosh
     * */
    public Item dequeue() {
        if(items.size() != 0) {
            Item item = items.get(0);
            items.remove(item);
            return item;
        }
        return null;
    }

    /**
     * Metoda getSize() kthen numrin e elementeve qe permban rradha
     * */
    public int getSize() {
        return items.size();
    }



}
