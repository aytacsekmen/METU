import java.util.ArrayList;

public class CengTree
{
    public CengTreeNode root;
    public CengTree(Integer order)
    {

        CengTreeNode.order = order;
        root= new CengTreeNodeLeaf(null);
    }
    private CengTreeNode hangiNodeEkle(CengBook book)
    {
        //Hangi node'a eklemem gerektiğini bulmaya çalışıyorum
        CengTreeNode araNode = root;
        while(araNode.getType() != CengNodeType.Leaf)
        {
            araNode = ((CengTreeNodeInternal) araNode).findPath(book.getBookID());
        }

        return araNode;
    }
    public void yazdirmak(Integer kac_node,ArrayList<CengTreeNode> nodeArray)
    {
        for(int i = 0; i < kac_node-1; i++)
        {
            //burada tek tek search'e giden nodeları printliyoruz
            CengTreeNodeInternal araNode = (CengTreeNodeInternal) nodeArray.get(i);
            Integer gecici_key_sayisi = araNode.keyCount();
            String kac_tane_tab = "\t".repeat(i);

            System.out.println(kac_tane_tab + "<index>");

            for(int j = 0; j < gecici_key_sayisi; j++)
            {
                //keyleri printle
                System.out.println(kac_tane_tab + araNode.keyAtIndex(j));
            }

            System.out.println(kac_tane_tab + "</index>");
        }
    }
    public void addBook(CengBook book)
    {
        CengTreeNodeLeaf hedefNode=((CengTreeNodeLeaf) hangiNodeEkle(book));

        hedefNode.addBook(book);
        if (hedefNode.bookCount()>2*CengTreeNode.order)
        {
            //eger book sayısı 2d yi geçerse yukarıya copyup yapmak lazım
            CengTreeNodeInternal ustNode = hedefNode.copyup();
            //eger bu durumda üst tarafın da key sayısı 2dyi geçerse onu da böleriz
            while(ustNode.keyCount() > 2*CengTreeNode.order)
            {
                //Pushup çağırıyorum.
                ustNode = ustNode.pushup();
            }
            if(ustNode.getParent() == null)
            {
                root = ustNode;
            }
        }
    }
    //bu fonksiyonu nodearray'ini bulmak için yazdım
    private CengTreeNode geciciFonksiyon(ArrayList<CengTreeNode> nodeArray,Integer id_book)
    {
        CengTreeNode tmp = root;
        while(tmp.getType() != CengNodeType.Leaf){
            nodeArray.add(tmp);
            tmp = ((CengTreeNodeInternal) tmp).findPath(id_book);
        }
        nodeArray.add(tmp);
        return tmp;
    }
    private Integer kacinci_sirada_bul (CengTreeNode sonuc,Integer bookID)
    {
        return  ((CengTreeNodeLeaf) sonuc).findBook(bookID);
    }

    public ArrayList<CengTreeNode> searchBook(Integer bookID)
    {
        ArrayList<CengTreeNode> nodeArray = new ArrayList<CengTreeNode>();
        CengTreeNode sonuc=geciciFonksiyon(nodeArray,bookID);
        int kac_node=nodeArray.size();
        Integer pos = kacinci_sirada_bul(sonuc,bookID);
        if(pos.equals(-1)) {
            System.out.println("Could not find " + bookID + ".");
            return null;
        }
        yazdirmak(kac_node,nodeArray);
        //CengTreeNode deneme=null;
        //deneme.yazdirmak (kac_node,nodeArray);

        CengBook hedef_kitap = ((CengTreeNodeLeaf) sonuc).getBook(pos);
        String kac_tane_tab = "\t".repeat(kac_node-1);
        System.out.println(kac_tane_tab + "<record>" + hedef_kitap.fullName() + "</record>");

        return nodeArray;
    }
    public void printTree()
    {
        //tepeden baslanarak print edilir
        root.btree_printer(0);
    }
}
