#pragma once
#include "../header.h"

/*
* How will you design the news feed feature in Facebook ?
*
* think about database design, what all information you would store in addition to news message
- news text
- data & time
- location
- reporter
- likes
- views ..etc

how would you store them in database efficiently for fast retrieval. how would you order/index them so that user sees the most relevant ones at the top.

These days almost real time updates would be required hence an effective caching strategy would also be required.

Use the observer pattern here.

Have a list of pages (friends, trending etc) that a user follows
In order of priority list the most recent posts according to time stamps
Refresh the feed every 2 mins or so


Guess this fits into publish subscribe model - Observer design pattern

1. Each user owns his/her data in his/her user area (data structure). Can be


class User {
    UserID id;  // unique id
    std::list<Update> self_updates; // owned by user; list of updates in reverse chrono order
    std::list<Update *> friend_updates;  // owned by user friends; list of updates in reverse chronological order
    std::list<User *> friends; // Friend list
};

class Update {
    UpdateType type; // media type of this update - can be photo/video etc
    DateTime timestamp;
    Message msg; // Message text in this update
    Media *media;   // can be pointer to photo/video/audio in the update OR NULL
    List<Comment> comments;  // Comments on this update
}
Now Publish(user, msg) will
1. Wrap the msg into Update data structure and add to the front of 'self_updates' list
2. For all the friends in 'friends' list, update their 'friend_updates' list with a pointer to this Update data structure (This is where the observer pattern comes).
Note: A user logged into the FB web UI will see the update when the browser polls the user area for any self/friend updates.

GetNewsFeed(user) will
1. Get the first 30 updates from 'self_updates' and 'friend_updates' sort them according to timestamp (these two are sorted according to timestamp individually). This will interleave self_updates between friend_updates.
2. Take the latest 30 updates from this sorted list to send back to browser UI.

Hope this design suffices.
*/