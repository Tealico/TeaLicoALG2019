//Ndertojme klasen per te realizuar WebCrawler-in
//e cila do te mbaje thelelsine dhe url-ne nga do filloj kerkimi
//dhe nje rradhe me elemente

import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.util.Scanner;

public class WebCrawler {
    private int depth;
    private ItemQueue queue;
    private String url;

    public WebCrawler(String url, int depth)
    {
        this.url = url;
        queue = new ItemQueue();
        this.depth = depth;
    }

    /*
    * Metoda getPageLinks mer si parameter nje element dhe ne qofte se thellesia e elementit
    * eshte me e madhe se thellesia e percaktuar nuk mund te kerkohet per url, ky eshte dhe kushti i
    * stopimit
    * Ne rast te kundert krijojme nje rradhe te re dhe nqs elementi qe duam te shtojme nuk ndodhet
    * ne rradhen me url atehere lexojme url per ate element,rritim thellesine me 1 per kete element,
    * lexojme cdo string qe permban url-ja dhe nqs
    * ndodhet nje element qe permban tekstin href="https:// atehere kemi gjetur nje url
    * dhe shtojme ne rradhen e krijuar ne fillim vetem nqs nuk ndodhet
    * Me pas bredhim gjith Rradhen e krijuar,heqim elementin e pare dhe me pas per kete element
    * therasim metoden getPageLinks rekursivisht e cila do te kerkoje perseri per url
    * vetem nqs nuk e tejkalone thellesine qe ka dhen perdoruesi
    * Kur arrihet thellesia perfundon ekzekutimi i metodes
     */
    private void getPageLinks(Item item)
    {
        int currentDepth = item.getDepth();
        if(currentDepth > depth)
            return;
        try {
            ItemQueue links = new ItemQueue();
            if(queue.enqueue(item)){
                currentDepth++;
                URL url = new URL(item.getUrl());
                Scanner in = new Scanner(url.openStream());
                while (in.hasNext()){
                    String next = in.next();
                    if (next.contains("href=\"https://")) {
                        String foundURL = "";
                        int start = next.indexOf("\"") + 1;
                        int end = next.lastIndexOf("\"");
                        foundURL = foundURL + next.substring(start,end);
                        links.enqueue(new Item(currentDepth,foundURL));
                    }
                }
                in.close();
                while(links.getSize() != 0)
                {
                    Item newItem = links.dequeue();
                    getPageLinks(newItem);
                }
            }
        }
        catch (IOException e) {
            return;
        }
    }

    /*
    * Metoda saveLinks merr si parameter emrin e skedarit ku duam te ruajm URL e gjetura
    * Ajo theret metoden getPageLinks e cila si fillim mer si parameter nje element te ri
    * me thellesi 0(thellesia minimale per te filluar kerkimin)
    * dhe url sa url e percaktuar nga perdoruesi per te filluar kerkimin dhe shkruan ne skedar
    * elementet e rradhes duke hequr nga rradha te parin dhe duke e afishuar ne skedar
    * me ane te metodes toString() afishon secilin ne baze te url dhe thellesise perkatese
    * Kjo perseritet deri sa rradhe te behet boshe
     */
    public void saveLinks(String fileName) throws IOException
    {
        getPageLinks(new Item(0,url));
        FileWriter out = new FileWriter(fileName, false);
        while(queue.getSize()!=0)
        {
            Item item = queue.dequeue();
            out.write(item.toString()+"\n");
        }
        out.close();
    }

    public static void main(String[] args)
    {
        try {
            String pageURL = args[0];
            int depth = Integer.parseInt(args[1]);
            String fileName = args[2];

            WebCrawler webCrawler = new WebCrawler(pageURL,depth);
            webCrawler.saveLinks(fileName);
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        catch (NumberFormatException e){
            e.printStackTrace();
        }
    }
}