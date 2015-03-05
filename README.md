# Drupal Module: Loft Offline
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

##Summary
**Provide a means to take a site offline totally, including blocking ALL login attempts by any user.**

You may also visit the [project page](http://www.drupal.org/project/loft_offline) on Drupal.org.

##Installation
1. Install as usual, see [http://drupal.org/node/70151](http://drupal.org/node/70151) for further information.

##Configuration with Drush
To take the site offline including blocking all logins by ALL users, use:
    
    drush vset loft_offline 1

Then to bring it back online:

    drush vdel loft_offline

## Configuration using MySQL
Drush is certainly the easier way to configure this module, however if you don't have access to Drush you can make direct queries to a MySQL database using the following.
(Be aware that if your tables are prefixed you will need to alter the following query).

To take the site offline including blocking all logins by ALL users, use:
    
    INSERT INTO `variable` (`name`, `value`) VALUES ('loft_offline', 's:1:"1";');
    DELETE FROM `cache_bootstrap` WHERE `cid` = 'variables';

Then to bring it back online:

    DELETE FROM `variable` WHERE `name` = 'loft_offline';
    DELETE FROM `cache_bootstrap` WHERE `cid` = 'variables';

##Suggested Use
1. Once this module is enabled, it will do nothing unless you set a single variable to true using drush (or editing the database variables table directly).
1. Once you set the variable `loft_offline` to 1, the site will be totally offline and the maintenance page will display for everyone; not even UID 1 will be able to access the site.

## Design Decisions/Rationale
1. At times I've needed to block access to the database entirely, including those users who normally would be able to login during normal maintenance mode.


##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>