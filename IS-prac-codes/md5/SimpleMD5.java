import java.util.Scanner;

public class SimpleMD5 {

    // Left Circular Shift
    static int leftRotate(int x, int c) {

        return (x << c) | (x >>> (32 - c));
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter text: ");

        String message = sc.nextLine();

        // Initial MD5 Buffers
        int A = 0x67452301;
        int B = 0xEFCDAB89;
        int C = 0x98BADCFE;
        int D = 0x10325476;

        System.out.println("\nInitial Buffers:");

        System.out.println("A = " + Integer.toHexString(A));
        System.out.println("B = " + Integer.toHexString(B));
        System.out.println("C = " + Integer.toHexString(C));
        System.out.println("D = " + Integer.toHexString(D));

        // Convert message to bytes
        byte[] bytes = message.getBytes();

        // Process each byte
        for(int i = 0; i < bytes.length; i++) {

            int M = bytes[i];

            // Simplified MD5 Function
            int F = (B & C) | (~B & D);

            int temp = A + F + M;

            // Left Rotate
            temp = leftRotate(temp, 5);

            // Update Buffers
            A = D;
            D = C;
            C = B;
            B = B + temp;

            System.out.println("\nStep " + (i+1));

            System.out.println("Character: " + (char)bytes[i]);

            System.out.println("ASCII: " + M);

            System.out.println("F Function: "
                    + Integer.toHexString(F));

            System.out.println("Updated A = "
                    + Integer.toHexString(A));

            System.out.println("Updated B = "
                    + Integer.toHexString(B));

            System.out.println("Updated C = "
                    + Integer.toHexString(C));

            System.out.println("Updated D = "
                    + Integer.toHexString(D));
        }

        // Final Digest
        String digest =
                Integer.toHexString(A) +
                Integer.toHexString(B) +
                Integer.toHexString(C) +
                Integer.toHexString(D);

        System.out.println("\nFinal MD5 Digest:");

        System.out.println(digest);

        sc.close();
    }
}