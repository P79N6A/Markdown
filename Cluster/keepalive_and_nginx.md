
#-- master --#
rrp_script chk_nginx {
    script "pidof nginx"
    interval 2
}

vrrp_instance VI_1 {

    interface eth1
    state MASTER
    priority 200

    virtual_router_id 33
    #unicast_src_ip 10.85.0.84
    #unicast_peer {
    #   10.85.0.83
    #}

    authentication {
       auth_type PASS
       auth_pass 123456
    }

    virtual_ipaddress {
       10.85.0.222
    }

    track_script {
       chk_nginx
    }

}

#-- slave --#

vrrp_script chk_nginx {
    script "pidof nginx"
    interval 2
}

vrrp_instance VI_1 {

    interface eth1
    state BACKUP
    priority 100
    advert_int 1

    virtual_router_id 33
    #unicast_src_ip 10.85.0.83
    #unicast_peer {
    #   10.85.0.84
    #}

   authentication {
       auth_type PASS
       auth_pass 123456
   }

   virtual_ipaddress {
      10.85.0.222
   }

   track_script {
       chk_nginx
   }
   
   
   
   
#---nginx 高可用配置---#
upstream master.jenkins.qcloud.com {

    server 10.85.0.84:8080 fail_timeout=3s;
    server 10.85.0.83:8080 backup;

}

server {
    listen       80;
    ignore_invalid_headers off;

    

    location / {

        proxy_connect_timeout 1s;
        proxy_pass http://master.jenkins.qcloud.com/;
    }

}

tcp反向代理支持

https://github.com/yaoweibin/nginx_tcp_proxy_module

