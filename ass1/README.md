# Assignment 1 Efficient Set ADT

<section class="exercise">
<header><h3>Changelog</h3></header>
<p>All important changes to the assignment specification and files will be listed here.</p>
<ul class="text-left">
	<li><code>[21/06 13:00]</code> Assignment released</li>
	<li><code>[25/06 17:20]</code> Clarified the array constraint and added more clarifications from the forum thread</li>
</ul>
</section>

<section class="exercise">
<header><h3>Aims</h3></header>
<ul>
	<li>To implement a set ADT using a balanced binary search tree and analyse the time complexity of its operations</li>
	<li>To give you practice with binary search trees and complexity analysis</li>
	<li>To appreciate the importance of using efficient data structures and algorithms</li>
</ul>
</section>

<section class="exercise">
<header><h3>Admin</h3></header>
<dl class="dl-horizontal">
	<dt>Marks</dt>
	<dd>contributes 15% towards your final mark see Assessment section for more details</dd>
	<dt>Submit</dt>
	<dd>see the Submission section</dd>
	<dt>Deadline</dt>
	<dd>8pm on Monday of Week 7</dd>
	<dt>Late penalty</dt>
	<dd>0.2% per hour or part thereof deducted from the attained mark, submissions later than 5 days not accepted</dd>
</dl>
</section>

<section class="exercise">
<header><h3>Prerequisite Knowledge</h3></header>
<ul>
	<li>Recursion</li>
	<li>Analysis of Algorithms</li>
	<li>Abstract Data Types</li>
	<li>Binary Search Trees</li>
	<li>Balanced BSTs including AVL Trees</li>
</ul>
</section>

<section class="exercise">
<header><h3>Background</h3></header>

<h4>Sets</h4>

<p>A <b>set</B> is a collection, or ensemble, of distinct items. We call these items <b>elements</b>, or <b>members</b> of the set. We can also say that they <i>belong to</i> that set. In this assignment, we are concerned with sets of integers.</p>

<p>Usually, we write a set by displaying its elements between two <i>curly braces</i>. For example, {1, 4, 6, 9} is a set whose elements are 1, 4, 6, 9. Note that the order in which the elements are written does not make the set different, so for example, {1, 4, 6, 9} and {6, 9, 1, 4} and {1, 6, 9, 4} all represent the same set.</p>

<h4>Notation</h4>

<p>Conventionally, sets are denoted by capital Roman letters and their elements denoted by small Roman letters.</p>

<p>Now let A and B be sets and v be an item.</p>

<ul>
	<li><p>v is said to be <strong>in</strong> A, written as vin A, if v is an element of A.</p></li>
	<li><p>Set A is said to be <strong>equal</strong> to set B, written as A = B, if both sets have the same elements. </p></li>
	<li><p>Set A is said to be a <strong>subset</strong> of set B, written as A subseteq B, if all elements of A are also elements of B. For example, we have that  {1,2,3} subseteq {1, 2,3,5} and  {1,5,8} nsubseteq {1, 5, 3,9}.</p></li>
</ul>

<h4>Operations on Sets</h4>

<p>In <a href="https://cgi.cse.unsw.edu.au/~cs2521/22T2/lecs/comp2521-22t2-2-2-abstract-data-types-adts.pdf"><strong>Lecture 2.2 - Abstract Data Types ADTs</strong></a>, we introduced some fundamental set operations:</p>

<ul>
	<li><p><strong>insert</strong> an item into a set</p></li>
	<li><p>check if an item is a <strong>member</strong> of a set</p></li>
	<li><p>check the <strong>size</strong>, or <strong>cardinality</strong>, of a set</p></li>
	<li><p><strong>display</strong> a set using standard set notation</p></li>
	<li><p>get the <strong>union</strong> of two sets</p></li>
	<li><p>get the <strong>intersection</strong> of two sets</p></li>
</ul>

<p>For those unfamiliar with set theory, we define union and intersection as follows:</p>

<div>
	<h5>Union</h5>
  <p>Let A and B be two sets. The <strong>union</strong> of A and B, denoted by A cup B, is the set of all elements that are contained in A, or B, or both A and B. Formally,</p>
  <p style="text-align: center;">
    [ A cup B = { x: xin A mbox{ or } xin B } ]
  </p>
  <p>For example:</p>
  <p style="text-align: center;">
    [ {1, 2, 3} cup {2, 4} = {1, 2, 3, 4} ]
    [ {1, 5} cup {2, 6, 8} = {1, 2, 5, 6, 8} ]
  </p>
</div>

<div>
	<h5>Intersection</h5>
  <p>Let A and B be two sets. The <strong>intersection</strong> of A and B, denoted by A cap B, is the set of all elements that are contained in both A and B. Formally,</p>
  <p style="text-align: center;">
    [ A cap B = {x : xin A mbox{ and } xin B} ]
  </p>
  <p>For example:</p>
  <p style="text-align: center;">
    [ {1,2,3} cap {2, 4} = {2} ]
    [ {1,5} cap {2,6,8} = emptyset ]
  </p>
</div>

<p>Here, we define a few more set operations: <strong>difference</strong>, <strong>floor</strong> and <strong>ceiling</strong>.</p>

<div>
	<h5>Difference</h5>

  <p>Let A and B be two sets. The <strong>difference</strong> of A and B, denoted by A - B, is the set of elements that are in A, but not in B. Formally,

  <p style="text-align: center;">
    [ A - B = {x : xin A mbox{ and } xnotin B} ]
  </p>

  <p>For example:</p>
  <p style="text-align: center;">
    [ {1,2,3} - {2,4} = {1, 3} ]
    [ {1,5} - {2,6,8} = {1,5} ]
  </p>

</div>

<div>
	<h5>Floor</h5>

  <p>Let A be a set and v be an item integer. The <strong>floor</strong> of v in A is the largest element in A that is less than or equal to v. Formally,

  <p style="text-align: center;">
    [ mbox{floor}A, v = max{x : xin A mbox{ and } x leq v} ]
  </p>

  <p>For example:</p>
  <p style="text-align: center;">
    [ mbox{floor}{1,2,3}, 5 = 3 ]
    [ mbox{floor}{1,5,8}, 5 = 5 ]
  </p>

  <p>Note that the <strong>floor</strong> of an item may not be defined if there are no elements in the set which are less than or equal to it. We discuss how to handle such cases below.</p>

</div>

<div>
	<h5>Ceiling</h5>

  <p>Let A be a set and v be an item integer. The <strong>ceiling</strong> of v in A is the smallest element in A that is greater than or equal to v. Formally,

  <p style="text-align: center;">
    [ mbox{ceiling}A, v = min{x : xin A mbox{ and } xgeq v} ]
  </p>

  <p>For example:</p>
  <p style="text-align: center;">
    [ mbox{ceiling}{1,5,8}, 6 = 8 ]
    [ mbox{ceiling}{1,5,8}, 5 = 5 ]
  </p>

  <p>Note that the <strong>ceiling</strong> of an item may not be defined if there are no elements in the set which are greater than or equal to it. We discuss how to handle such cases below.</p>

</div>

<h4 class="mt-3">Set ADT</h4>

<p>A set is an example of an abstract data type: there is a collection of operations that can be performed on them, but the exact details of the implementation are unimportant, as long as they produce the desired behaviour from the user's perspective.</p>

<p>In lectures, we considered several different implementations of the Set ADT: unordered/ordered arrays and unordered/ordered linked lists. Although these were relatively simple to implement, each of them were flawed/inefficient in some way:</p>

<table class="table table-sm table-bordered">
	<tr>
		<td></td>
		<td><b>Unordered</b></td>
		<td><b>Ordered</b></td>
	</tr>
	<tr>
		<td><b>Array</b></td>
		<td>Insertion requires On membership query<br/>
		    Search requires On linear scan
		</td>
		<td>Insertion requires On array shift to maintain order</td>
	</tr>
	<tr>
		<td><b>Linked List</b></td>
		<td>Insertion/search requires On traversal of the list</td>
		<td>Insertion/search requires On traversal of the list</td>
	</tr>
</table>

<p>We then introduced binary search trees as a data structure that could have improved search and insertion costs. But these operations are only guaranteed to be efficient if the tree is relatively balanced. Thus, your task in this assignment will be to implement a Set ADT using a <b>balanced binary search tree</b>.</p>

<h4 class="mt-3">Cursors</h4>

<p>As you have learned, an ADT does not provide users access to the internal representation of the data type. But what if a user wanted to know what elements are contained in a set? With only the basic operations listed above, the only way the user could do this is to check every possible item for membership in the set, like so:</p>

<pre>
i = smallest possible integer
while i <= largest possible integer:
	check if i is in the set
	i = i + 1
</pre>

<p>However, this is not feasible given how many possible integers there are. Therefore, many collection data types provide access to items via cursors or iterators. Cursors provide a relatively simple way for users to iterate over the items in a collection:</p>

<pre>
let s be a set
c = create a cursor for s
while thereIsStillANextItemc:
	i = getNextItemc
</pre>

</section>

<section class="exercise">
<header><h3>Setting Up</h3></header>
<p>Change into the directory you created for the assignment and run the following command:</p>

<pre is="tty">
<kbd is="sh">unzip <a href="https://cgi.cse.unsw.edu.au/~cs2521/22T2/ass/ass1/downloads/files.zip">/web/cs2521/22T2/ass/ass1/downloads/files.zip</a></kbd>
</pre>

<p>If you're working at home, download <code>files.zip</code> by clicking on the above link and then run the <tt>unzip</tt> command on the downloaded file.</p>

<p>You should now have the following files:</p>

<dl class="dl-horizontal">
	<dt><code>Makefile</code></dt>
	<dd>a set of dependencies used to control compilation</dd>
	<dt><code>Set.h</code></dt>
	<dd>interface to the Set ADT - <span><b>cannot be modified</b></span></dd>
	<dt><code>Set.c</code></dt>
	<dd>implementation of the Set ADT incomplete</dd>
	<dt><code>SetStructs.h</code></dt>
	<dd>definition of structs used in the Set ADT incomplete</dd>
	<dt><code>testSet.c</code></dt>
	<dd>a main program containing some basic tests for the Set ADT</dd>
	<dt><code>analysis.txt</code></dt>
	<dd>a template for you to enter your time complexity analysis for selected functions</dd>
</dl>

<p>Usually, the structs used by an ADT implementation are defined in the <code>.c</code> file along with the functions. However, in this assignment, they are defined in a separate file, <code>SetStructs.h</code>, because our tests will need access to these structs in order to make it easier to independently test each function, as well as to check whether your trees are balanced. You may add extra fields to these structs and define additional structs if needed, but you must use the given structs/fields in your implementation as follows:</p>

<ul>
	<li>You must use <code>struct node</code> for binary search tree nodes</li>
	<li>The elements of the set must be stored in the <code>item</code> fields of the <code>struct node</code></li>
	<li>The <code>left</code> and <code>right</code> pointers should be used to connect a tree node to its left and right subtrees respectively</li>
	<li>The <code>tree</code> field must be used to point to the binary search tree that stores all the elements of the set</li>
</ul>

<p>Note that the only files that you are allowed to submit are <code>Set.c</code>, <code>SetStructs.h</code> and <code>analysis.txt</code>. This means all your code for implementing the Set ADT must be placed in <code>Set.c</code>, <i>except</i> the struct definitions which should be in <code>SetStructs.h</code>.</p>

</section>

<section class="exercise with-self">
<header><h3>Task 1: Implementation</h3></header>

<p>Your task is to use a <span><b>balanced binary search tree</b></span> to implement a <b>Set</b> ADT with the aforementioned operations. We have broken the operations up into groups - you must fully implement all the operations in each group before moving on to the next group.</p>

<div class="alert alert-primary mt-3">
<h4>Note</h4>
<p>When we say you must use a <b>balanced</b> binary search tree, we mean a <b>height-balanced</b> binary search tree. This means for every node in the tree, the absolute difference in height between its left and right subtrees must be no greater than 1.</p>
</div>

<div class="alert alert-warning mt-3">
<h4>Important Constraint</h4>
<p>The method of converting the given trees into an array or linked list, solving the main problem using the array/linked list and then returning the result or converting the result back into a tree is strictly forbidden, as such solutions go against the spirit of using binary search trees.</p>
</div>

<h4>Group 1: Basic Operations</h4>

<table class="mt-3 table table-sm table-bordered">
	<tr>
		<th>Operation/Function</th>
		<th>Description</th>
	</tr>
	<tr>
		<td><code>SetNew</code></td>
		<td>Creates a new empty set</td>
	</tr>
	<tr>
		<td><code>SetFree</code></td>
		<td>Frees all memory associated with the given set</td>
	</tr>
	<tr>
		<td><code>SetInsert</code></td>
		<td>Inserts an item into the given set. Any integer may be inserted including negative integers except for the value <code>UNDEFINED</code>.<br/>
		    <span class="red"><b>Note:</b></span> The worst-case time complexity of this function must be Olog n. Inefficient solutions will be heavily penalised.
		</td>
	</tr>
	<tr>
		<td><code>SetSize</code></td>
		<td>Returns the number of elements in the given set</td>
	</tr>
	<tr>
		<td><code>SetContains</code></td>
		<td>Checks if an item is in the given set. Returns true if it is, and false otherwise.</td>
	</tr>
	<tr>
		<td><code>SetShow</code></td>
		<td>Prints the elements in the given set in ascending order between curly braces, with items separated by a comma and space. <b>Do not print a newline.</b> Examples:
<pre>
{}
{2}
{2, 4}
{2, 4, 7, 8}
</pre>
		</td>
	</tr>
</table>

<h4>Group 2: Further Operations</h4>

<table class="mt-3 table table-sm table-bordered">
	<tr>
		<th>Operation/Function</th>
		<th>Description</th>
	</tr>
	<tr>
		<td><code>SetUnion</code></td>
		<td>Given two sets A and B, returns a new set A cup B defined above</td>
	</tr>
	<tr>
		<td><code>SetIntersection</code></td>
		<td>Given two sets A and B, returns a new set A cap B defined above</td>
	</tr>
	<tr>
		<td><code>SetDifference</code></td>
		<td>Given two sets A and B, returns a new set A - B defined above</td>
	</tr>
	<tr>
		<td><code>SetEquals</code></td>
		<td>Returns true if the two given sets contain the same elements, and false otherwise.</td>
	</tr>
	<tr>
		<td><code>SetSubset</code></td>
		<td>Given two sets, returns true if the first set is a subset of the second set, and false otherwise.</td>
	</tr>
	<tr>
		<td><code>SetFloor</code></td>
		<td>Given a set A and an item v, returns  mbox{floor}A, v  defined above or <code>UNDEFINED</code> if the result is undefined. <code>UNDEFINED</code> is <code>#define</code>d in <code>Set.h</code>, and you may assume that this value is never inserted into the set via <code>SetInsert</code>. You may also assume that this function is never given <code>UNDEFINED</code> as the item.</td>
	</tr>
	<tr>
		<td><code>SetCeiling</code></td>
		<td>Given a set A and an item v, returns  mbox{ceiling}A, v  defined above or <code>UNDEFINED</code> if the result is undefined. You may assume that this function is never given <code>UNDEFINED</code> as the item.</td>
	</tr>
</table>

<h4>Group 3: Cursor Operations</h4>

<div class="alert alert-primary mt-3">
	This is a challenge! You should not expect to receive hints for this part.<br/>
	<b>Note:</b> You may need to modify some of your existing code to get this working.
</div>

<p>As described above, cursors provide a way for users to iterate over elements of the set without accessing the internal representation of the set. There are three cursor operations:</p>

<table class="mt-3 table table-sm table-bordered">
	<tr>
		<th>Operation/Function</th>
		<th>Description</th>
	</tr>
	<tr>
		<td><code>SetCursorNew</code></td>
		<td>Creates a cursor for the given set, initially positioned at the smallest element of the set</td>
	</tr>
	<tr>
		<td><code>SetCursorFree</code></td>
		<td>Frees all memory associated with the given cursor</td>
	</tr>
	<tr>
		<td><code>SetCursorNext</code></td>
		<td>Returns the element at the cursor's current position, and then moves the cursor to the next greatest element. If there is no next greatest element, then all subsequent calls to <code>SetCursorNext</code> on this cursor should return <code>UNDEFINED</code>.<br/>
		</td>
	</tr>
</table>

<p>Here is an example of how a cursor would be used:</p>

<div class="highlight"><pre><span></span><span class="kt">int</span> <span class="nf">main</span><span class="p"></span><span class="kt">void</span><span class="p"></span> <span class="p">{</span>
	<span class="n">Set</span> <span class="n">s</span> <span class="o">=</span> <span class="n">SetNew</span><span class="p">;</span>
	<span class="n">SetInsert</span><span class="p"></span><span class="n">s</span><span class="p">,</span> <span class="mi">7</span><span class="p">;</span>
	<span class="n">SetInsert</span><span class="p"></span><span class="n">s</span><span class="p">,</span> <span class="mi">4</span><span class="p">;</span>
	<span class="n">SetInsert</span><span class="p"></span><span class="n">s</span><span class="p">,</span> <span class="mi">8</span><span class="p">;</span>
	<span class="n">SetInsert</span><span class="p"></span><span class="n">s</span><span class="p">,</span> <span class="mi">1</span><span class="p">;</span>
	<span class="n">SetCursor</span> <span class="n">cur</span> <span class="o">=</span> <span class="n">SetCursorNew</span><span class="p"></span><span class="n">s</span><span class="p">;</span>
	<span class="kt">int</span> <span class="n">item</span><span class="p">;</span>
	<span class="k">while</span> <span class="p"></span><span class="n">item</span> <span class="o">=</span> <span class="n">SetCursorNext</span><span class="p"></span><span class="n">cur</span><span class="p"></span> <span class="o">!=</span> <span class="n">UNDEFINED</span><span class="p"></span> <span class="p">{</span>
		<span class="n">printf</span><span class="p"></span><span class="s">&quot;%d &quot;</span><span class="p">,</span> <span class="n">item</span><span class="p">;</span>
	<span class="p">}</span>
	<span class="n">SetCursorFree</span><span class="p"></span><span class="n">cur</span><span class="p">;</span>
	<span class="n">SetFree</span><span class="p"></span><span class="n">s</span><span class="p">;</span>
<span class="p">}</span>
</pre></div>

<p>This would produce the output:</p>

<pre>
1 4 7 8 
</pre>

<p>The following are some clarifications about the expected behaviour of the cursor:</p>

<ul>
	<li><p>A user should be able to create multiple cursors for a given set and iterate over the set independently with each cursor.</p></li>

  <li><p><code>SetCursorNext</code> should continue to work as described above if elements are inserted after the cursor has been created.<p>

  <ul>
    <li><p>For example, suppose a set contains the elements 2, 5 and 8, and a cursor is currently positioned at element 5. If 7 is now inserted into the set, then calling <code>SetCursorNext</code> should return 5, then 7, then 8, then <code>UNDEFINED</code>. But if 3 was inserted instead, then <code>SetCursorNext</code> will not return 3, as cursors only move forwards, not backwards.</p></li>
  </ul>

</ul>

<p>In order to obtain full marks for this part, all cursor operations should have a worst-case time complexity of O1. A solution where the cursor operations have a worst-case time complexity of Olog n is worth half the marks. Solutions that are slower than this will not receive marks for this part.</p>

<p>You must also explain the design and implementation of your solution and how it met the time complexity requirement of O1 or Olog n in <code>analysis.txt</code>.</p>

</section>

<section class="exercise with-self">
<header><h3>Task 2: Complexity Analysis</h3></header>

<p>You are required to determine the worst-case time complexity of <b>your implementation</b> of the following operations, and write your answers in <code>analysis.txt</code> along with an explanation of each answer.</p>

<ul>
	<li>SetUnion</li>
	<li>SetIntersection</li>
	<li>SetDifference</li>
	<li>SetEquals</li>
	<li>SetSubset</li>
	<li>SetFloor</li>
	<li>SetCeiling</li>
</ul>

<p>Your answers should be in big-O notation. If an operation involves two sets, then the time complexity should be in terms of n and m, the sizes of the two sets respectively, otherwise it should just be in terms of n, the size of the one set.</p>

<p>In your explanations, you may use time complexities established in lectures without proof, as long as you indicate that it was established in lectures. For example, you may use the fact that the worst-case time complexity of searching in an AVL tree is Olog n, as this was established in lectures.</p>

</section>

<section class="exercise">
<header><h3>Testing</h3></header>
<p>We have provided a main program <code>testSet.c</code> containing basic test cases. You should examine <code>testSet.c</code> to see what the tests do and how the tests call your functions.</p>

<p>To run these tests, first run <code>make</code>, which compiles your code and creates an executable called <code>testSet</code>, and then run <code>./testSet</code>.</p>

<p>All of the given tests except for <code>SetShow</code> are assertion-based, which means that the program will exit as soon as a test fails. If you want to ignore a test for the time being, then you can comment out the corresponding function which runs that test.</p>

<p>We strongly recommend you to add your own tests, as the given tests are very simple. You can easily add your own tests by creating a new function in <code>testSet.c</code> and then calling it from the <code>main</code> function. You are also free to completely restructure the testing program if you want.</p>

</section>

<section class="exercise">
<header><h3>Debugging</h3></header>
<p>Debugging is an important and inevitable aspect of programming. We expect everyone to have an understanding of basic debugging methods, including using print statements, knowing basic GDB commands and running Valgrind. In the forum and in help sessions, tutors will expect you to have made a reasonable attempt to debug your program yourself using these methods before asking for help.</p>

<p>You can learn about GDB and Valgrind in the <a href="https://cgi.cse.unsw.edu.au/~cs2521/22T2/lab/11/questions" target="_blank">Debugging with GDB and Valgrind</a> lab exercise.</p>
</section>

<section class="exercise">
<header><h3>Frequently Asked Questions</h3></header>

<ul>
	<li><b>Are we allowed to create our own functions?</b> You are always allowed to create your own functions. All additional functions you create should be made <code>static</code>.</li>
	<li><b>Are we allowed to create our own <code>#define</code>s and structs?</b> Yes.</li>
	<li><b>Are we allowed to modify <code>Set.h</code> in any way?</b> No.</li>
	<li><b>Are we allowed to change the signatures of the given functions?</b> No. If you change these, your code won't compile and we won't be able to test it.</li>
	<li><b>What errors do we need to handle?</b> You should handle common errors such as <code>NULL</code> returned from <code>malloc</code> by printing an error message to <code>stderr</code> and terminating the program. You are not required to handle other errors.</li>
	<li><b>What invalid inputs do we need to handle?</b> You are not required to handle invalid inputs, such as <code>NULL</code> being passed in as a set. It is the user's responsibility to provide valid inputs.</li>
	<li><b>Will we be assessed on our tests?</b> No. You will not be submitting any test files, and therefore you will not be assessed on your tests.</li>
	<li><b>Are we allowed to share tests?</b> No. Testing is an important part of software development. Students that test their code more will likely have more correct code, so to ensure fairness, each student should independently develop their own tests.</li>
</ul>
</section>

<section class="exercise">
<header><h3>Submission</h3></header>
<p>You must submit the files <code>Set.c</code>, <code>SetStructs.h</code> and <code>analysis.txt</code>. You can submit via the command line using the <code>give</code> command:</p>

<pre is="tty">
<kbd is="sh">give cs2521 ass1 Set.c SetStructs.h analysis.txt</kbd>
</pre>

<p>You can also submit via <a href="https://cgi.cse.unsw.edu.au/~give/Student/give.php" target="_blank">give's web interface</a>. You can submit multiple times. Only your last submission will be marked. You can check the files you have submitted <a href="https://cgi.cse.unsw.edu.au/~cs2521/22T2/view/main.cgi/" target="_blank">here</a>.</p>

<aside class="warning">
	<p>After you submit, you <b>must</b> check that your submission was successful by going to your <a href="https://www.cse.unsw.edu.au/~cs2521/22T2/view/main.cgi/" target="_blank">submissions page</a>. Check that the timestamp is correct. If your submission does not appear under Last Submission or the timestamp is not correct, then resubmit.</p>
</aside>

<h5>Compilation</h5>

<p>You must ensure that your final submission compiles on CSE machines. Submitting non-compiling code leads to extra administrative overhead and will result in a 10% penalty.</p>

<p>Every time you make a submission, a dryrun test will be run on your code to check that it compiles. Please ensure that your final submission successfully compiles, even for parts that you have not completed.</p>

</section>

<section class="exercise">
<header><h3>Assessment Criteria</h3></header>
<p>This assignment will contribute 15% to your final mark.</p>

<h4>Correctness</h4>

<p><b>76%</b> of the marks for this assignment will be based on the correctness of your code, and will be based on autotesting. Marks for correctness will be distributed as follows:</p>

<table class="table table-sm table-bordered table-striped">
	<tr>
		<td rowspan="5">Group 1</td>
		<td>SetFree</td>
		<td>See <b>memory errors/leaks</b> section below</td>
	</tr>
	<tr>
		<td>SetInsert</td>
		<td>18%</td>
	</tr>
	<tr>
		<td>SetSize</td>
		<td>2%</td>
	</tr>
	<tr>
		<td>SetContains</td>
		<td>2%</td>
	</tr>
	<tr>
		<td>SetShow</td>
		<td>4%</td>
	</tr>
	<tr>
		<td rowspan="7">Group 2</td>
		<td>SetUnion</td>
		<td>6%</td>
	</tr>
	<tr>
		<td>SetIntersection</td>
		<td>6%</td>
	</tr>
	<tr>
		<td>SetDifference</td>
		<td>6%</td>
	</tr>
	<tr>
		<td>SetEquals</td>
		<td>6%</td>
	</tr>
	<tr>
		<td>SetSubset</td>
		<td>6%</td>
	</tr>
	<tr>
		<td>SetFloor</td>
		<td>6%</td>
	</tr>
	<tr>
		<td>SetCeiling</td>
		<td>6%</td>
	</tr>
	<tr>
		<td rowspan="1">Group 3</td>
		<td>SetCursorNew, SetCursorFree, SetCursorNext</td>
		<td>8%</td>
	</tr>
</table>

<p>Please note that we expect you to prioritise completing functions correctly over implementing as many functions as possible potentially incorrectly, so partial marks will not be awarded. You are expected to exercise your debugging skills to fix problems with the function you are currently working on, before moving on to the next function.</p>

<h5>Memory errors/leaks</h5>

<p>You must ensure that your code does not contain memory errors or leaks, as code that contains memory errors is unsafe and it is bad practice to leave memory leaks in your program.</p>

<p>Our tests will include a memory error/leak test for each operation. If a memory error/leak arises from your code, you will receive a penalty which is 10% of the marks for that operation. For example, the penalty for causing a memory error/leak in the <code>SetEquals</code> operation will be 0.6%. Note that our tests will always call <code>SetFree</code> at the end of the test and <code>SetCursorFree</code> if appropriate to free all memory associated with the set.</p>

<h4>Complexity analysis</h4>
<p><b>14%</b> of the marks for this assignment will be based on the correctness of your complexity analysis in <code>analysis.txt</code> and the quality of your explanations.</p>

<h4>Style</h4>

<p><b>10%</b> of the marks for this assignment will come from hand marking of the readability of the code you have written. These marks will be awarded on the basis of clarity, commenting, elegance and style. The following is an indicative list of characteristics that will be assessed, though your program will be assessed wholistically so other characteristics may be assessed too see the <a href="https://cgi.cse.unsw.edu.au/~cs2521/22T2/resources/style_guide.html" target="_blank">style guide</a> for more details:</p>

<ul>
	<li>Consistent and sensible indentation and spacing</li>
	<li>Using blank lines and whitespace</li>
	<li>Using functions to avoid repeating code</li>
	<li>Decomposing code into functions and not having overly long functions</li>
	<li>Using comments effectively and not leaving planning or debugging comments</li>
</ul>

<p>The course staff may vary the assessment scheme after inspecting the assignment submissions but it will remain broadly similar to the description above.</p>
</section>

<section class="exercise">
<header><h3>Originality of Work</h3></header>
<p>This is an individual assignment. The work you submit must be your own work and only your work apart from the exceptions below. Joint work is not permitted. At no point should a student read or have a copy of another student's assignment code.</p>

<p>You may use any amount of code from the lectures and labs of the <b>current iteration</b> of this course. You must clearly attribute the source of this code in a comment.</p>

<p>You may use small amounts &lt; 10 lines of general purpose code not specific to the assignment obtained from sites such as Stack Overflow or other publicly available resources. You must clearly attribute the source of this code in a comment.</p>

<p>You are not permitted to request help with the assignment apart from in the course forum, help sessions or from course lecturers or tutors.</p>

<p>Do not provide or show your assignment work to any other person including by posting it publicly on the forum apart from the teaching staff of COMP2521. When posting on the course forum, teaching staff will be able to view the assignment code you have recently submitted with give.</p>

<p>The work you submit must otherwise be entirely your own work. Submission of work partially or completely derived from any other person or jointly written with any other person is not permitted. The penalties for such an offence may include negative marks, automatic failure of the course and possibly other academic discipline. Assignment submissions will be examined both automatically and manually for such issues.</p>

<p>Relevant scholarship authorities will be informed if students holding scholarships are involved in an incident of plagiarism or other misconduct. If you knowingly provide or show your assignment work to another person for any reason, and work derived from it is submitted, then you may be penalised, even if the work was submitted without your knowledge or consent. This may apply even if your work is submitted by a third party unknown to you.</p>
</section>
