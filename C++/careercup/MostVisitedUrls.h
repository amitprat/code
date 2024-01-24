#include "../Header.h"

/*
https://www.careercup.com/question?id=4681660918398976

Given a large network of computers, each keeping log files of visited urls, find the top ten of the most visited urls.
(i.e. have many large <string (url) -> int (visits)> maps, calculate implicitly <string (url) -> int (sum of visits among 
all distributed maps), and get the top ten in the combined map)

The result list must be exact, and the maps are too large to transmit over the network (especially sending all of them to a 
central server or using MapReduce directly, is not allowed)
*/

/*
Presuming a protocol exists that can ask three questions to each server:

* the score of a single url
* the top 10
* the top n that satisfy score >= N

We program a two pass solution like so:

We denote the number of servers as S.

[First pass]
(1) Ask every server for its own top ten

(2) merge the results. For all URLs in the merged set calculate correct values by asking
all servers for their scores for each URL. Calculate a set of top ten from our sample.

(3) pick score of the now tenth URL as the threshold that we try to beat
in the second round. We denote the threshold as T.

[Second pass]
(4) Ask every server for all its top N that satisfy score >= T/S

(5) Merge these bigger samples again as in step (2)

(6) We now have the correct top ten with correct scores.
*/