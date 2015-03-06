# Drupal Module: Loft Offline
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

##Summary
**Provide a mechanism to put a Drupal 7 site into extreme maintenance mode, which includes blocking ALL login by any user including user 1.**

* Allows for a delayed maintenance mode with optional user alert message.

##Installation
1. Install as usual, see [http://drupal.org/node/70151](http://drupal.org/node/70151) for further information.
1. Grant the following permission to all roles you wish to be alerted for pending maintenance _View advance warning_.
1. To enable the ui, you will need to enable the variable_admin module, then, you may configure settings at admin/config/system/variable.

## Going into extreme maintenance mode
**Once the site has gone offline, it can only be brought back using either Drush or directly modifying the database.  Examples are shown below.**

You have options:
1. Use drush (see below)
1. Through the ui at `admin/config/system/variable/edit/loft_offline`
1. Directly in the database.

## Coming out of extreme maintenance mode
You have less options (the UI is not available because you cannot access the website using the browser).
1. Use drush (see below)
1. Directly in the database.

##Configuration with Drush
To immediately take the site offline including blocking all logins by ALL users, use:
    
    drush vset loft_offline 1

Then to bring it back online:

    drush vdel loft_offline

To take the site offline in 10 minutes specify the number of seconds like this:

    drush vset loft_offline 600

**Be aware that you must refresh a drupal page after bringing the site online again, before you can setup a new delay.** _Technically speaking, merely setting the variable to 0 is not enough to bring the site online, you have to load a page._


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