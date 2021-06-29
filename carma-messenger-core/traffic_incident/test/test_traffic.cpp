/*
 * Copyright (C) 2020-2021 LEIDOS.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include "traffic_incident_worker.h"
#include "traffic_incident_node.h"
#include <gtest/gtest.h>

namespace traffic
{

TEST(TrafficIncidentWorkerTest, testTrafficMobilityOperationBroadcastStrategyParams)
{

    TrafficIncidentWorker traffic_worker([](auto msg){});
  
    gps_common::GPSFix msg;
   
    msg.latitude=57.1;
    msg.longitude=155.79;
    msg.header.stamp.sec=25;

    //traffic_worker.setPinPoint(msg);

    std::string sender_id="USDOT-49096";
    std::string closed_lane="[1]";
    double down_track=50.1;
    double up_track=50.1;
    double min_gap=4.1;
    double advisory_speed=10;
    std::string event_reason="MOVE OVER LAW";
    std::string event_type="CLOSED";
    
    traffic_worker.setSenderId(sender_id);
    traffic_worker.setDownTrack(down_track);
    traffic_worker.setUpTrack(up_track);
    traffic_worker.setMinGap(min_gap);
    traffic_worker.setAdvisorySpeed(advisory_speed);
    traffic_worker.setEventReason(event_reason);
    traffic_worker.setEventType(event_type);

    cav_msgs::MobilityOperation traffic_msg=traffic_worker.mobilityMessageGenerator(msg);
 
    EXPECT_EQ(traffic_msg.strategy_params,"lat:57.1,lon:155.79,downtrack:50.1,uptrack:50.1,min_gap:4.1,advisory_speed:10,event_reason:MOVE OVER LAW,event_type:CLOSED");
  
  }

  TEST(TrafficIncidentWorkerTest, testTrafficMobilityOperationBroadcastTimeStamp)
{

    TrafficIncidentWorker traffic_worker([](auto msg){});
  
    gps_common::GPSFix msg;
   
    msg.latitude=57.1;
    msg.longitude=155.79;
    msg.header.stamp.sec=25;

    std::string sender_id="USDOT-49096";
    std::string closed_lane="[1]";
    double down_track=50.1;
    double up_track=50.1;
    double min_gap=4.1;
    double advisory_speed=10;
    std::string event_reason="MOVE OVER LAW";
    std::string event_type="CLOSED";
        
    traffic_worker.setSenderId(sender_id);
    traffic_worker.setMinGap(min_gap);
    traffic_worker.setDownTrack(down_track);
    traffic_worker.setUpTrack(up_track);
    traffic_worker.setAdvisorySpeed(advisory_speed);
    traffic_worker.setEventReason(event_reason);
    traffic_worker.setEventType(event_type);

    cav_msgs::MobilityOperation traffic_msg=traffic_worker.mobilityMessageGenerator(msg);
 
    EXPECT_EQ(traffic_msg.header.timestamp,25000);
 
  }

  TEST(TrafficIncidentWorkerTest, testTrafficMobilityOperationBroadcastStrategy)
{

    TrafficIncidentWorker traffic_worker([](auto msg){});
  
    gps_common::GPSFix msg;
   
    msg.latitude=57.1;
    msg.longitude=155.79;
    msg.header.stamp.sec=25;

    std::string sender_id="USDOT-49096";
    std::string closed_lane="[1]";
    double down_track=50.1;
    double up_track=50.1;
    double min_gap=4.1;
    double advisory_speed=10;
    std::string event_reason="MOVE OVER LAW";
    std::string event_type="CLOSED";

    traffic_worker.setSenderId(sender_id);
    traffic_worker.setMinGap(min_gap);
    traffic_worker.setDownTrack(down_track);
    traffic_worker.setUpTrack(up_track);
    traffic_worker.setAdvisorySpeed(advisory_speed);
    traffic_worker.setEventReason(event_reason);
    traffic_worker.setEventType(event_type);

    cav_msgs::MobilityOperation traffic_msg=traffic_worker.mobilityMessageGenerator(msg);
 
    EXPECT_EQ(traffic_msg.header.sender_id,"USDOT-49096");
    EXPECT_EQ(traffic_msg.strategy,"carma3/Incident_Use_Case");
  
  }
   
    TEST(TrafficIncidentWorkerTest, testAnyTypeToStringFunction)
{
   TrafficIncidentWorker traffic_worker([](auto msg){});
 
   EXPECT_EQ(traffic_worker.anytypeToString(55.6712),"55.6712");
}


    TEST(TrafficIncidentWorkerTest, testGettersSetters)
{
   TrafficIncidentWorker traffic_worker([](auto msg){});
    traffic_worker.setSenderId("USDOT-49096");
    traffic_worker.setMinGap(1.2);
    traffic_worker.setDownTrack(1.2);
    traffic_worker.setUpTrack(1.2);

    gps_common::GPSFix msg; 
    msg.latitude=57.1;
    msg.longitude=155.79;
    msg.header.stamp.sec=25;


    traffic_worker.setPinPoint(msg);
    traffic_worker.setAdvisorySpeed(1.2);
    traffic_worker.setEventReason("MOVE OVER LAW");
    traffic_worker.setEventType("CLOSED");
    
    EXPECT_EQ(traffic_worker.getSenderId(),"USDOT-49096");
    EXPECT_EQ(traffic_worker.getMinGap(),1.2);
    EXPECT_EQ(traffic_worker.getDownTrack(),1.2);
    EXPECT_EQ(traffic_worker.getUpTrack(),1.2);
    EXPECT_EQ(traffic_worker.getPinPoint().latitude,57.1);
    EXPECT_EQ(traffic_worker.getAdvisorySpeed(),1.2);
    EXPECT_EQ(traffic_worker.getEventReason(),"MOVE OVER LAW");
    EXPECT_EQ(traffic_worker.getEventType(),"CLOSED");
}

}//traffic