* Taken from Careercup
* We can think about
- reducing the response time of the server
---- by using a distributed system to share the load based on geography
---- by using a central server but many caching servers at various geographical locations
---- what would be the right database design

- reducing the storage space
---- database design

- backup and failover

- security issues
---- prevent people from creating links to ---whatever---

- handling old/obsolete urls
---- may be, while creating the url we can say to the user that it will be deleted if the url is never used for more than say 3 years
---- may be allow the user to login and delete unused ones

- how a company like bit.ly is going to make profit out of this service! how can that be improved

- user friendly things
---- browser plugins to speed up creating links (youtube sharing has an option to create short urls)
---- giving report to user about the usage statistics
---- mobile app to create urls quickly

Redirect Part:

When you click on a link of any tiny url, an HTTP Request is sent to their server with the full URL, like http // bit.ly / b9 (not a real one).

They read the path part (here b9), which maps to their Database.

In the Database, they find the real URL. Then they issue a redirect, which is a HTTP 302 response and the target URL in the header.

Encoding Part:

One of the most popular URL shortening services simply take the ID in the database of the URL and then convert it to Base 62[a-zA-Z0-9].


import static org.testing.AssertJUnit.assertEquals ;

public class TinyURL {
    private static final String ALPHABET_MAP = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" ;
    private static final int BASE = ALPHABET_MAP.length() ;

    public static String encode ( int IndexNum ) {
        StringBuilder sb = new StringBuilder() ;

        while ( IndexNum > 0 ) {
            sb.append ( ALPHABET_MAP.charAt ( IndexNum % BASE ) ) ;
            IndexNum /= BASE ;
        }
        return sb.reverse().toString() ;
    }

    public static int decode ( String str ) {
        int Num = 0 ;

        for ( int i = 0, len = str.length(); i < len; i++ ) {
            Num = Num * BASE + ALPHABET_MAP.indexOf ( str.charAt(i) ) ;
        }
        return Num ;
    }

    public static void main ( String[] args ) {
        //System.out.println ( "Encoding for 123 is " + encode(123) ) ;
        //System.out.println ( "Decoding for b9 is " + decode ("b9" ) ) ;

        assertEquals ( "b9", encode(123) ) ;
        assertEquals ( 123, decode("b9") ) ;
    }
    }

* https://www.educative.io/courses/grokking-the-system-design-interview/m2ygV4E81AR

Database Schema: #
We would need two tables: one for storing information about the URL mappings and one for the user’s data who created the short link.

URL: TinyUrl(PK), Original Url, Creation Time, Expiration Time
User: Id, Name,...

# Encoding actual URL #
We can compute a unique hash (e.g., MD5 or SHA256, etc.) of the given URL. The hash can then be encoded for display. This encoding could be base36 ([a-z ,0-9]) or base62 ([A-Z, a-z, 0-9]) and if we add ‘+’ and ‘/’ we can use Base64 encoding. A reasonable question would be, what should be the length of the short key? 6, 8, or 10 characters?

Using base64 encoding, a 6 letters long key would result in 64^6 = ~68.7 billion possible strings.
Using base64 encoding, an 8 letters long key would result in 64^8 = ~281 trillion possible strings.

With 68.7B unique strings, let’s assume six letter keys would suffice for our system.

If we use the MD5 algorithm as our hash function, it’ll produce a 128-bit hash value. After base64 encoding, we’ll get a string having more than 21 characters (since each base64 character encodes 6 bits of the hash value). Now we only have space for 8 characters per short key; how will we choose our key then? We can take the first 6 (or 8) letters for the key. This could result in key duplication; to resolve that, we can choose some other characters out of the encoding string or swap some characters.

##What are the different issues with our solution? We have the following couple of problems with our encoding scheme:

If multiple users enter the same URL, they can get the same shortened URL, which is not acceptable.
What if parts of the URL are URL-encoded? e.g., http://www.educative.io/distributed.php?id=design, and http://www.educative.io/distributed.php%3Fid%3Ddesign are identical except for the URL encoding.
Workaround for the issues: We can append an increasing sequence number to each input URL to make it unique and then generate its hash. We don’t need to store this sequence number in the databases, though. Possible problems with this approach could be an ever-increasing sequence number. Can it overflow? Appending an increasing sequence number will also impact the performance of the service.

Another solution could be to append the user id (which should be unique) to the input URL. However, if the user has not signed in, we would have to ask the user to choose a uniqueness key. Even after this, if we have a conflict, we have to keep generating a key until we get a unique one.