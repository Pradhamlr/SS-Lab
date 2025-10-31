SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION is_palindrome(n VARCHAR2)
RETURN VARCHAR2
IS
    rev VARCHAR2(100) := '';
    i NUMBER;
BEGIN
    FOR i IN REVERSE 1..LENGTH(n) LOOP
        rev := rev || SUBSTR(n, i, 1);
    END LOOP;

    IF rev = n THEN
        RETURN n || ' is a PALINDROME.';
    ELSE
        RETURN n || ' is NOT a PALINDROME.';
    END IF;
END;
/
BEGIN
    DBMS_OUTPUT.PUT_LINE(is_palindrome('&n'));
END;



SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE check_palindrome(n VARCHAR2)
IS
    rev VARCHAR2(100) := '';
    i NUMBER;
BEGIN
    FOR i IN REVERSE 1..LENGTH(n) LOOP
        rev := rev || SUBSTR(n, i, 1);
    END LOOP;

    IF rev = n THEN
        DBMS_OUTPUT.PUT_LINE(n || ' is a PALINDROME.');
    ELSE
        DBMS_OUTPUT.PUT_LINE(n || ' is NOT a PALINDROME.');
    END IF;
END;
/
BEGIN
    check_palindrome('&n');
END;