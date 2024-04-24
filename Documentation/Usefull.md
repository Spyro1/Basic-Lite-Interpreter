
You can improve testability of your classes by not using cin and cout directly. Instead use istream& and ostream& to pass in the input source and output sink as parameters. This is a case of dependency injection. If you do that, you can pass in a std::stringstream instead of cin, so that you can provide specified input and get at the output from your test framework.

That said, you can achieve a similar effect by turning cin and cout into stringstreams (at least temporarily). To do this, set up a std::stringbuf (or "borrow" one from a std::stringstream) and use cin.rdbuf(my_stringbuf_ptr) to change the streambuf used by cin. You may want to revert this change in test teardown. To do that you can use code like:

### std::cin testing
```cpp
    stringbuf test_input("One line of input with no newline", ios_base::in);
    streambuf * const cin_buf = cin.rdbuf(&test_input);
    test_func(); // uses cin and cout
    cin.rdbuf(cin_buf);
```

### std::cout testing

```cpp
    stringbuf test_output(ios_base::out);
    streambuf * const cout_buf = cout.rdbuf(&test_output);
    test_func(); // uses cin and cout
    cout.rdbuf(cout_buf);
    string test_output_text = test_output.str(); // Test result
```
