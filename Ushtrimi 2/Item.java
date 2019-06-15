// Krijojme nje klas Item e cila na mban per cdo element
// nje vlere e tipit numer i plote per thellesine dhe
// nje String per url

public class Item {
    private int depth;
    private String url;

    public Item(int depth, String url) {
        this.depth = depth;
        this.url = url;
    }

    public int getDepth() {
        return depth;
    }

    public String getUrl() {
        return url;
    }

    //Metoda toString() afishon vleren e thellesiste per kete element
    //dhe permbajtjen e URL
    public String toString() {
        String s = "";
        for(int i = 0; i < depth; i++)
            s += "     ";
        s = s + "Thellsesia " + depth + " >> " +url;
        return s;
    }
}
