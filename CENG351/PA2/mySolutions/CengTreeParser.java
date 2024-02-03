import java.io.IOException;
import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;

public class CengTreeParser
{
    public static ArrayList<CengBook> parseBooksFromFile(String filename) {
        ArrayList<CengBook> bookList = new ArrayList<CengBook>();

        // You need to parse the input file in order to use GUI tables.
        // TODO: Parse the input file, and convert them into CengBooks
        Scanner scanner = null;
        String okunacakSatir;

        try {
            File input_file = new File(filename);
            scanner = new Scanner(input_file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        while (scanner.hasNextLine()) {
            okunacakSatir = scanner.nextLine();
            String[] tmp = okunacakSatir.split("[|]");

            Integer bookId = Integer.parseInt(tmp[0]);
            String bookTitle = tmp[1];
            String author = tmp[2];
            String genre = tmp[3];

            CengBook cengBook = new CengBook(bookId, bookTitle, author, genre);
            bookList.add(cengBook);
        }
            return bookList;
        }

        public static void startParsingCommandLine () throws IOException
        {
            // TODO: Start listening and parsing command line -System.in-.
            // There are 4 commands:
            // 1) quit : End the app, gracefully. Print nothing, call nothing, just break off your command line loop.
            // 2) add : Parse and create the book, and call CengBookRunner.addBook(newlyCreatedBook).
            // 3) search : Parse the bookID, and call CengBookRunner.searchBook(bookID).
            // 4) print : Print the whole tree, call CengBookRunner.printTree().

            // Commands (quit, add, search, print) are case-insensitive.

            Scanner scanner = new Scanner(System.in);
            String command_line;
            String command;

            while (true)
            {
                command_line = scanner.nextLine();
                String[] inp_array = command_line.split("[|]");
                command = inp_array[0];

                if (command.equalsIgnoreCase("quit"))
                {
                    break;
                    //return;
                }

                if (command.equalsIgnoreCase("add"))
                {
                    Integer bookid = Integer.parseInt(inp_array[1]);
                    String bookTitle = inp_array[2];
                    String author = inp_array[3];
                    String genre = inp_array[4];
                    CengBook book1 = new CengBook(bookid, bookTitle, author, genre);
                    CengBookRunner.addBook(book1);
                }
                if (command.equalsIgnoreCase("search"))
                {
                    Integer key = Integer.parseInt(inp_array[1]);
                    CengBookRunner.searchBook(key);

                }
                if (command.equalsIgnoreCase("print"))
                {
                    CengBookRunner.printTree();
                }
            }
        }

    }