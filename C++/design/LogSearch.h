#pragma once
#include "../header.h"

/*
* There is a cluster of servers. In this cluster some group of servers are running application A, some group are running B, etc. Each application server produces huge logs and the log file sizes run into GBs. Each minute there are millions of log entries.

You need to design a system that allows you to:
1. Specify the name of the application whose logs you want to search.
2. Search any text that the log message may contain.
3. Search within a time stamp range.
4. Search within the specified log level(s).

The system should be real-time.

Piped grep commands aside, you're probably better off with either Amazon Kinesis -> Spark -> Elasticsearch or similar architecture or using 3rd-party solutions like Logly. That said, here's a typical recommended approach.

1. Each application logger and usage should include the application and component name, along with timestamp, level, and message from an initial design perspective.

2. Either add a log "wrapper" to each application that persists them to a queue, cache or central data mart. An alternative approach would be to make sure log rotation enabled on the server and tail logs and pipe to a "wrapper" to export them to central location. Another alternative (my preference) is to use Logstash to consume log messages and ship them to external store, usually Kafka or Kinesis topics.

3. Consumer groups may grok/normalize the various log entries if not already standardized and republish normalized version to another "topic" in Kafka or Kinesis. You could also use a stream processor built into Kafka or 3rd-party like Spark if necessary.

4. Again leverage Logstash to consume normalized topics and publish to Elasticsearch or other Lucene-based search engine with document store. Be sure to add index rotation to data mart later (perhaps beyond 15 days' records) or your cluster will become massive.

5. Spin up Kibana to allow searchable browser-based interface and various dashboards and visualizations, plus time-series data analysis plugins.

6. Add either server-side alerting using Nagios or Monit, or you can use commercial products like Elastic's X-Pack "Watcher". Personally I use Monit and have custom shell script that triggers webhook message to a Slack channel for various system alerts.
*/